#include "fake_motor.h"

static int current_motor_angle;

void FAKE_MOTOR_set_angle(int given_angle){

    current_motor_angle = given_angle;

}

int FAKE_MOTOR_get_angle(){

    return current_motor_angle;

}

void FAKE_MOTOR_init(){

    current_motor_angle = 140;

}
