#include "fake_motor.h"
#include "../../source/motor/motor.h"

static void FAKE_MOTOR_set_angle(int);
static int FAKE_MOTOR_get_angle();
static void FAKE_MOTOR_init();

static int current_motor_angle;
void (*MOTOR_set_angle)(int) = FAKE_MOTOR_set_angle;
void (*MOTOR_init)() = FAKE_MOTOR_init;
int (*MOTOR_get_angle)() = FAKE_MOTOR_get_angle;

static void FAKE_MOTOR_set_angle(int given_angle){

    current_motor_angle = given_angle;

}

static int FAKE_MOTOR_get_angle(){

    return current_motor_angle;

}

static void FAKE_MOTOR_init(){

    current_motor_angle = MIN_SPEED_ANGLE;

}
