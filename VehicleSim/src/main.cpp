/*
 * main.cpp
 *
 *  Created on: Mar 11, 2019
 *      Author: Ryan
 */

#include <iostream>
#include <fstream>
#include <cmath>
#include <Eigen/Dense>
#include "simple_vehicle.hpp"

using namespace std;

int main()
{
	cout << "Hello world!\n";
	float dt = 0.01;
	SimpleVehicle vehicle(10.0, 0.0, 0.0, dt);
	ofstream log("log.csv");
	log << "\"speed\",\"yaw\",\"yaw_rate\",\"steering_angle\",\"x\",\"y\"" << endl;

	for (int i = 0; i < 1000; i++)
	{
		inputs_t inputs;
		inputs.steering_angle = 30.0 / 180.0 * M_PI * cos(2.0 * M_PI * 0.25 * i * dt);
		vehicle.step(inputs);
		log << vehicle.v << "," << vehicle.yaw << "," << vehicle.yaw_rate << "," << vehicle.inputs.steering_angle <<
			   "," << vehicle.x << "," << vehicle.y << endl;
	}

	return 0;
}
