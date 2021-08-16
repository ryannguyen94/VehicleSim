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
#include <stdint.h>

#include "simple_vehicle.hpp"
#include "mpc.hpp"

using namespace std;

int main()
{
	cout << "Hello world!\n";
	float dt = 0.01;
	float v = 5.0;
	SimpleVehicle vehicle(5.0, 0.0, 0.0, dt);

	// Sanity check MPC
	Eigen::MatrixXd A(6, 6);
	Eigen::MatrixXd B(6, 1);
	Eigen::MatrixXd C(2, 6);
	Eigen::MatrixXd Q(1, 1);
	Eigen::MatrixXd R(1, 1);
	float Np = 10;
	float Nc = 4;
	float a = 0.952380955;

	/**
	 * x = [x xdot y ydot yaw yaw_rate]
	 */
	A << 1.0, dt, 0.0, 0.0, 0.0, 0.0,
	     0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
		 0.0, 0.0, 1.0, dt, 0.0, 0.0,
		 0.0, 0.0, 0.0, 0.0, v, 0.0,
		 0.0, 0.0, 0.0, 0.0, 1.0, dt,
		 0.0, 0.0, 0.0, 0.0, 0.0, a;
	B << 0.0, 0.0, 0.0, 0.0, 0.0, v * (1.0 - a) / vehicle.w;
	C << 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
	     0.0, 0.0, 0.0, 0.0, 1.0, 0.0;
	R << 0.01;

	Mpc<Eigen::MatrixXd> test_mpc(A, B, C, R, Np, Nc);

	string sep = "\n----------------------------------\n";
	cout << "A" << endl;
	cout << test_mpc.A << sep;
	cout << "B" << endl;
	cout << test_mpc.B << sep;
	cout << "C" << endl;
	cout << test_mpc.C << sep;
	cout << "R" << endl;
	cout << test_mpc.R << sep;
	cout << "F" << endl;
	cout << test_mpc.F << sep;
	cout << "phi" << endl;
	cout << test_mpc.phi << sep;

	ofstream log("log.csv");
	log << "\"speed\",\"yaw\",\"yaw_rate\",\"steering_angle\",\"x\",\"y\"" << endl;

	for (int i = 0; i < 1000; i++)
	{
		Eigen::MatrixXd target;
		target = Eigen::MatrixXd::Ones(Np*2, 1);
		for (uint16_t i = 0u; i < Np; ++i)
		{
			target(2 * i + 1) = 0;
		}
		Eigen::MatrixXd x(6, 1);
		x << vehicle.x,
			 vehicle.v * cos(vehicle.yaw),
			 vehicle.y,
			 vehicle.v * sin(vehicle.yaw),
			 vehicle.yaw,
			 vehicle.yaw_rate;
		Eigen::MatrixXd steering = test_mpc.step(x, target);
		cout << "x" << endl;
		cout << x << sep;
		cout << "delta_u" << endl;
		cout << steering << sep;

		inputs_t inputs;
		inputs.steering_angle = steering(0, 0);
		vehicle.step(inputs);
		log << vehicle.v << "," << vehicle.yaw << "," << vehicle.yaw_rate << "," << vehicle.inputs.steering_angle <<
			   "," << vehicle.x << "," << vehicle.y << endl;
	}

	return 0;
}
