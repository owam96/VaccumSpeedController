#include "speed_controller.h"
#include "../../test/speed_controller_test/speed_controller_test.h"
#include "../motor/motor.h"
#include "../../test/fake_motor/fake_motor.h"

static SPEED_t current_speed;

void SPEED_CONTROLLER_init(){

    current_speed = MED;
    MOTOR_set_angle(MED_SPEED_ANGLE);

}

SPEED_t SPEED_CONTROLLER_get_speed(){
    int current_motor_angle = FAKE_MOTOR_get_angle();
    if(current_motor_angle == MIN_SPEED_ANGLE){
        return MIN;
    }
    else if(current_motor_angle == MED_SPEED_ANGLE){
        return MED;
    }
    else if(current_motor_angle == MAX_SPEED_ANGLE){
        return MAX;
    }
    else{
        return UNKNOWN;
    }

}

void SPEED_CONTROLLER_set_speed(SPEED_t given_speed){
    current_speed = given_speed;
    if(current_speed == MIN){
        MOTOR_set_angle(MIN_SPEED_ANGLE);
    }
    else if(current_speed == MED){
        MOTOR_set_angle(MED_SPEED_ANGLE);
    }
    else if(current_speed == MAX){
        MOTOR_set_angle(MAX_SPEED_ANGLE);
    }
}
