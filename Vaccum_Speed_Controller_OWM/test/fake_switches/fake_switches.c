#include "fake_switches.h"
#include "../../source/switches/switches.h"
#include "../fake_timer/fake_timer.h"
#include "../../source/timer/timer.h"
#include "../../source/speed_controller/speed_controller.h"

static int current_speed;
static SWITCH_STATE_t p_switch_state;

void FAKE_SWITCHES_positive_press(){

current_speed = SPEED_CONTROLLER_get_speed();
if(current_speed == MIN)
    SPEED_CONTROLLER_set_speed(MED);
else if (current_speed == MED)
    SPEED_CONTROLLER_set_speed(MAX);

}

void FAKE_SWITCHES_negative_press(){

current_speed = SPEED_CONTROLLER_get_speed();

if(current_speed == MAX)
    SPEED_CONTROLLER_set_speed(MED);
else if (current_speed == MED)
    SPEED_CONTROLLER_set_speed(MIN);


}

SWITCH_STATE_t FAKE_SWITCHES_p_get_state(){

    return p_switch_state;

}

void FAKE_SWITCHES_p_release(){
    p_switch_state = RELEASED;
}

void FAKE_SWITCHES_p_press(long long int duration_ms){

    current_speed = SPEED_CONTROLLER_get_speed();
    p_switch_state = PRESSED;

    TIMER_STATE_t timer_state;
    FAKE_TIMER_start(duration_ms);
    while(FAKE_SWITCHES_p_get_state() == PRESSED && (timer_state = FAKE_TIMER_get_state()) == RUNNING){
        if(duration_ms >= 30000){
            FAKE_TIMER_set_state(DONE);
        }
        else{
            FAKE_SWITCHES_p_release();
        }

    }
    if(timer_state == DONE){
        if(current_speed == MAX){
            SPEED_CONTROLLER_set_speed(MED);
        }
    else if (current_speed == MED){
            SPEED_CONTROLLER_set_speed(MIN);
    }
    }
    else{
        return;
    }

}
