#ifndef MCP_HPP_
#define MCP_HPP_

#include <stdint.h>

template<class matrix>
class Mpc {
    public:
        matrix A, B, C, Q, R, F, delta_U, phi;
        float Np, Nc;
        uint8_t x_size, u_size, y_size;

        Mpc(matrix mA,
            matrix mB,
            matrix mC,
            matrix mQ,
            matrix mR);
        matrix step(matrix x);
}

#endif  // MCP_HPP_