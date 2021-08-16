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

#ifndef MCP_HPP_
#define MCP_HPP_

#include <iostream>
#include <stdint.h>
#include <stdexcept>

template<class matrix>
class Mpc {
    public:
        matrix A, B, C, R, F, delta_U, phi, R_bar;
        float Np, Nc;
        uint8_t x_size, u_size, y_size;

        Mpc(
            matrix mA,
            matrix mB,
            matrix mC,
            matrix mR,
            float Np,
            float Nc)
            : A(mA),
              B(mB),
              C(mC),
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
                throw std::invalid_argument("A is not square");
            x_size = A.rows();

            // Check B dimension
            if (B.rows() != x_size)
                throw std::invalid_argument("B row does not equal A row");
            u_size = B.cols();

            // Check C dimension
            if (C.cols() != x_size)
                throw std::invalid_argument("C col does not equal A col");
            y_size = C.rows();

            // Check R dimension
            if ((R.rows() != R.cols())
                || (R.rows() != u_size))
                throw std::invalid_argument("Invalid R dimension");

            F = matrix::Zero(y_size * Np, x_size);
            phi = matrix::Zero(y_size * Np, u_size * Nc);
            R_bar = matrix::Identity(Nc, Nc) * R(0, 0);

            matrix tmp_CA = C;
            for (uint16_t i = 0u; i < Np; ++i)
            {
                tmp_CA *= A;
                F.block(i * y_size, 0, y_size, x_size) = tmp_CA;
            }

            matrix CA = C;
            for (uint16_t i = 0u; i < Np; ++i)
            {
                for (uint16_t j = 0; j < Nc; ++j)
                {
                	matrix CAB = CA * B;
                    if ((i + j + 1) * y_size <= phi.rows()
                        && ((j+1) * u_size <= phi.cols()))
                    {
                        phi.block((i+j) * y_size, j * u_size, y_size, u_size) = CAB;
                        std::cout << phi << std::endl;
                    }
                    else
                    {
                        break;
                    }
                }
                CA *= A;
            }
        }

        matrix step(matrix x, matrix target)
        {
//        	matrix tmp = (target - F * x);
//        	std::cout << "tmp" << std::endl;
//        	std::cout << tmp << std::endl;
        	matrix delta_u = (phi.transpose() * phi + R_bar).inverse() * phi.transpose() * (target - F * x);
        	return delta_u;
        }
};

#endif  // MCP_HPP_
