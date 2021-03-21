#include "fake_switches.h"
#include "../../source/switches/switches.h"
#include "../fake_timer/fake_timer.h"
#include "../../source/timer/timer.h"
#include "../../source/speed_controller/speed_controller.h"

static int current_speed;
static SWITCH_STATE_t pos_switch_state;
static SWITCH_STATE_t neg_switch_state;
static SWITCH_STATE_t p_switch_state;
static long long int p_duration_MS;

/* Fake functions prototypes */
static void FAKE_SWITCHES_init();
static void FAKE_SWITCHES_positive_press();
static SWITCH_STATE_t FAKE_SWITCHES_pos_get_state();
static void FAKE_SWITCHES_negative_press();
static SWITCH_STATE_t FAKE_SWITCHES_neg_get_state();
static void FAKE_SWITCHES_p_press(long long int);
static SWITCH_STATE_t FAKE_SWITCHES_p_get_state();
static void FAKE_SWITCHES_p_release();
static void FAKE_SWITCHES_update();

/* Function pointers to point to fake functions during tests */
void (*SWITCHES_init)() = FAKE_SWITCHES_init;
void (*SWITCHES_positive_press)() = FAKE_SWITCHES_positive_press;
SWITCH_STATE_t (*SWITCHES_pos_get_state)() = FAKE_SWITCHES_pos_get_state;
void (*SWITCHES_negative_press)() = FAKE_SWITCHES_negative_press;
SWITCH_STATE_t (*SWITCHES_neg_get_state)() = FAKE_SWITCHES_neg_get_state;
void (*SWITCHES_p_press)(long long int) = FAKE_SWITCHES_p_press;
SWITCH_STATE_t (*SWITCHES_p_get_state)() = FAKE_SWITCHES_p_get_state;
void (*SWITCHES_p_release)() = FAKE_SWITCHES_p_release;
void (*SWITCHES_update)() = FAKE_SWITCHES_update;

static void FAKE_SWITCHES_init(){
    pos_switch_state = neg_switch_state = p_switch_state = RELEASED;

}

static void FAKE_SWITCHES_positive_press(){

current_speed = SPEED_CONTROLLER_get_speed();
if(current_speed == MIN)
    SPEED_CONTROLLER_set_speed(MED);
else if (current_speed == MED)
    SPEED_CONTROLLER_set_speed(MAX);

}

static SWITCH_STATE_t FAKE_SWITCHES_pos_get_state(){

    return pos_switch_state;

}

static void FAKE_SWITCHES_negative_press(){

current_speed = SPEED_CONTROLLER_get_speed();

if(current_speed == MAX)
    SPEED_CONTROLLER_set_speed(MED);
else if (current_speed == MED)
    SPEED_CONTROLLER_set_speed(MIN);


}

static SWITCH_STATE_t FAKE_SWITCHES_neg_get_state(){

    return neg_switch_state;

}

static SWITCH_STATE_t FAKE_SWITCHES_p_get_state(){

    return p_switch_state;

}

static void FAKE_SWITCHES_p_release(){
    p_switch_state = RELEASED;
}

static void FAKE_SWITCHES_p_press(long long int duration_ms){

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

void FAKE_SWITCHES_pos_set_state(SWITCH_STATE_t new_pos_state){

    pos_switch_state = new_pos_state;

}

void FAKE_SWITCHES_neg_set_state(SWITCH_STATE_t new_neg_state){

    neg_switch_state = new_neg_state;

}
void FAKE_SWITCHES_p_set_state(SWITCH_STATE_t new_p_state, long long int new_press_time){

    p_switch_state = new_p_state;
    p_duration_MS = new_press_time;

}


static void FAKE_SWITCHES_update(){

    if(p_switch_state == PREPRESSED || p_switch_state == PRESSED){
        SWITCHES_p_press(p_duration_MS);
        return;
    }
    else if(neg_switch_state == PREPRESSED || neg_switch_state == PRESSED){
        SWITCHES_negative_press();
        return;
    }
    else if(pos_switch_state == PREPRESSED || pos_switch_state == PRESSED){
        SWITCHES_positive_press();
        return;
    }
    else{
        return;
    }

}
