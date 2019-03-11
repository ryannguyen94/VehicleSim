/*
 * wheel.hpp
 *
 *  Created on: Mar 11, 2019
 *      Author: Ryan
 */

#ifndef INC_WHEEL_HPP_
#define INC_WHEEL_HPP_

typedef struct 
{
    float D, C, B;
} magicFormula;

class Wheel {
    public:
		float v, w, slip;
        Wheel(magicFormula mf, float radius, float inertia, float m, float B, float ts, float v0, float w0);
        void step(float downForce, float torque);
    protected:
        magicFormula mf;
        float R, I, ts, B, m;
        float calcLongTraction(float slip, float downForce);
        float calcSlipRatio(float v, float w, float radius);
};



#endif /* INC_WHEEL_HPP_ */
