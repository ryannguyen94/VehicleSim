/*
 * filter.h
 *
 *  Created on: Feb 3, 2018
 *      Author: ryan
 */

#ifndef FILTER_H_
#define FILTER_H_

class Filter {
    public:
    	float freq;
    	float dt;
    	float prev_state;
    	Filter() : freq(0), dt(0), prev_state(0), a(0) {}
        Filter(float freq, float dt, float prev_state) : freq(freq), dt(dt), prev_state(prev_state), a(0) {}
        float step(float input);
    protected:
        float a;
};

#endif /* FILTER_H_ */
