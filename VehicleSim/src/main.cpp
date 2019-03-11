/*
 * main.cpp
 *
 *  Created on: Mar 11, 2019
 *      Author: Ryan
 */

#include <iostream>
#include "wheel.hpp"

using namespace std;

int main()
{
	cout << "Hello world!\n";
	magicFormula mf = {2.5, 1.28, 20.9};
	float radius = 0.5;
	float inertia = 1.0;
	float mass = 2;
	float B = 0.1;
	float ts = 0.01;
	Wheel* wheel;
	wheel = new Wheel(mf, radius, inertia, mass, B, ts, 0, 0/0.5);

	for (int i = 0; i < 1000; i++)
	{
		wheel->step(20, 100);
		printf("speed: %f, angular speed: %f, slip: %f\n", wheel->v, wheel->w, wheel->slip);
	}

	delete wheel;
	return 0;
}
