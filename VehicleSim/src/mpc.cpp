/**
 * x = [x y yaw yaw_rate]
 * A = linearized of
 *     x = x + v * cos(yaw) * dt
 *     y = y + v * sin(yaw) * dt
 *     yaw = yaw + yaw_rate * dt
 *     yaw_rate = v * steering / w
 * B = [0 0 0 v/w]
 * C = [0 1 0 0]
 */
#include <stdexcept>

#include "mpc.hpp"

Mpc::Mpc(
    matrix mA,
    matrix mB,
    matrix mC,
    matrix mQ,
    matrix mR,
    float Np,
    float Nc)
    : A(mA),
      B(mB),
      C(mC),
      Q(mQ),
      R(mR),
      Np(Np),
      Nc(Nc)
{
    /**
     * Dimension check
     * A = x_size x x_size
     * B = x_size x u_size
     * C = y_size x x_size
     * Q = x_size x x_size
     * R = u_size x u_size
     * F = y_size * Np x x_size
     * phi = y_size * Np x u_size * Nc
     **/

    // Check if A is square
    if (A.rows() != A.cols())
        throw invalid_argument("A is not square");
    x_size = A.rows();

    // Check B dimension
    if (B.rows() != x_size)
        throw invalid_argument("B row does not equal A row");
    u_size = B.cols();

    // Check C dimension
    if (C.cols() != x_size)
        throw invalid_argument("C col does not equal A col");
    y_size = C.rows();

    // Check Q dimension
    if ((Q.rows() != Q.cols())
        || (Q.rows() != x_size))
        throw invalid_argument("Invalid Q dimension");

    // Check R dimension
    if ((R.rows() != R.cols())
        || (R.rows() != u_size))
        throw invalid_argument("Invalid R dimension");

    F = matrix::Zero(y_size * Np, x_size);
    phi = matrix::Zero(y_size * Np, u_size * Nc);

    matrix tmp_CA = C;
    for (uint16_t i = 0u; i < Np; ++i)
    {
        tmp_CA *= A;
        F.block(i * y_size, 0, y_size, x_size) = tmp_CA;
    }
    matrix temp_CAB = C;
    for (uint16_t i = 0u; i < Np; ++i)
    {
        matrix CAB = tmp_CAB * B;
        for (uint16_t j = 0; j < Nc; ++j)
        {
            if ((i + j + 1) * y_size <= phi.rows()
                && ((j+1) * u_size <= phi.cols()))
            {
                phi.block((i+j) * y_size, j * u_size, y_size, u_size) = CAB;
            }
            else
            {
                break;
            }
        }
    }

}
