/*
 * filter.c
 *
 *  Created on: Feb 3, 2018
 *      Author: ryan
 */

#include "filter.hpp"

float Filter::step(float input) {
    this->a = 1.0/(1.0 + this->freq * this->dt);
    float out = this->prev_state * this->a + input * (1.0-this->a);
    this->prev_state = out;
    return out;
}
