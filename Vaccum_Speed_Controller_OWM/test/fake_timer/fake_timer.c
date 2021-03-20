#include "fake_timer.h"
#include "../../source/timer/timer.h"

static TIMER_STATE_t timer_state;

void FAKE_TIMER_start(long long int time_ms){

    timer_state = RUNNING;

}

TIMER_STATE_t FAKE_TIMER_get_state(){

    return timer_state;

}

void FAKE_TIMER_set_state(TIMER_STATE_t given_state){

    timer_state = given_state;

}
