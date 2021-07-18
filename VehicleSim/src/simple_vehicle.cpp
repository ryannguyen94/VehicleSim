#include <math.h>
#include "simple_vehicle.hpp"
#include "filter.hpp"

SimpleVehicle::SimpleVehicle(
    float v,
    float yaw_rate,
    float yaw,
    float dt)
    : v(v),
      yaw_rate(yaw_rate),
      yaw(yaw),
      dt(dt),
      x(0.0),
      y(0.0),
      cof(1.0),
      yaw_intent(Filter(1.0, dt, yaw_rate))
{
    this->w = 3.449;
}


void SimpleVehicle::step(inputs_t inputs)
{
    this->inputs = inputs;
    this->yaw_rate = calcYawRate();
    this->yaw += this->yaw_rate * this->dt;
    this->x += this->v * cos(this->yaw);
    this->y += this->v * sin(this->yaw);
}

float SimpleVehicle::calcYawRate()
{
    return this->yaw_intent.step(this->inputs.steering_angle * this->v / this->w);
}
