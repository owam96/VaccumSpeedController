#include "../../source/timer/timer.h"

#ifndef FAKE_TIMER_H_INCLUDED
#define FAKE_TIMER_H_INCLUDED

void FAKE_TIMER_start(long long int);

TIMER_STATE_t FAKE_TIMER_get_state();

void FAKE_TIMER_set_state(TIMER_STATE_t);

#endif // FAKE_TIMER_H_INCLUDED
