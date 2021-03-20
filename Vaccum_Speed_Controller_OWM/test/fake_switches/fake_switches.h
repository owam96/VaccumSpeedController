#include "../../source/switches/switches.h"

#ifndef FAKE_SWITCHES_H_INCLUDED
#define FAKE_SWITCHES_H_INCLUDED

void FAKE_SWITCHES_positive_press();
void FAKE_SWITCHES_negative_press();

SWITCH_STATE_t FAKE_SWITCHES_p_get_state();

void FAKE_SWITCHES_p_press(long long int);

void FAKE_SWITCHES_p_release();



#endif // FAKE_SWITCHES_H_INCLUDED
