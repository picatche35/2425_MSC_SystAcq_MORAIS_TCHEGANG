/*
 * motor.h
 *
 *  Created on: Nov 21, 2024
 *      Author: eugen
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_


void motor_speed(int speed);
void motor_on();
void motor_off();
void motor_start();
void measure_current();
struct motor;

typedef struct motor{
	int speed;
	int last_speed;
}motor_t;


#endif /* INC_MOTOR_H_ */
