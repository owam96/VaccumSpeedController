#include "fake_motor.h"

static void FAKE_MOTOR_set_angle(int);
int FAKE_MOTOR_get_angle();
static void FAKE_MOTOR_init();

static int current_motor_angle;
extern void (*MOTOR_set_angle)(int) = FAKE_MOTOR_set_angle;
extern void (*MOTOR_init)() = FAKE_MOTOR_init;

static void FAKE_MOTOR_set_angle(int given_angle){

    current_motor_angle = given_angle;

}

int FAKE_MOTOR_get_angle(){

    return current_motor_angle;

}

static void FAKE_MOTOR_init(){

    current_motor_angle = 140;

}
