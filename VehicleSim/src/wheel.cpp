/*
 * wheel.cpp
 *
 *  Created on: Mar 11, 2019
 *      Author: Ryan
 */

#include "wheel.hpp"
#include <cmath>
#include <algorithm>

Wheel::Wheel(magicFormula mfCoeff, float radius, float inertia, float mass, float damping, float samplingTime, float v0, float w0)
{
	mf = mfCoeff;
	R = radius;
	I = inertia;
	ts = samplingTime;
	v = v0;
	w = w0;
	B = damping;
	m = mass;
	slip = calcSlipRatio(v, w, radius);
}

void Wheel::step(float downForce, float torque)
{
	slip = calcSlipRatio(v, w, R);
	float longForce = calcLongTraction(slip, downForce);
	w = ((torque - longForce*R - B*w) / I) * ts + w;
	v = longForce / m * ts + v;
}

float Wheel::calcLongTraction(float slip, float downForce)
{
	return downForce * 0.6 * mf.D*sin(mf.C*atan(mf.B*slip));
}

float Wheel::calcSlipRatio(float v, float w, float radius)
{
	if (v < 0)
	{
		return 0.0;
	}
	else
	{
		return (w*radius - v) / std::max(v, 3.0F);
	}
}

