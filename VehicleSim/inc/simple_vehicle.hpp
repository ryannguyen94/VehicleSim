#ifndef SIMPLE_VEHICLE_HPP
#define SIMPLE_VEHICLE_HPP

#include "filter.hpp"

typedef struct
{
    float aped, steering_angle;
} inputs_t;

class SimpleVehicle {
    public:
        inputs_t inputs;
        float v, yaw_rate, yaw, dt, x, y, w;
        SimpleVehicle(float vx, float yaw_rate, float yaw, float dt);
        void step(inputs_t inputs);
    protected:
        float cof;
        float calcYawRate();
        Filter yaw_intent;

};

#endif  // SIMPLE_VEHICLE_HPP
