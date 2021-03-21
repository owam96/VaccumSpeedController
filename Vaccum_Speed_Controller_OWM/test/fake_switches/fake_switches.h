#include "../../source/switches/switches.h"

#ifndef FAKE_SWITCHES_H_INCLUDED
#define FAKE_SWITCHES_H_INCLUDED

void FAKE_SWITCHES_pos_set_state(SWITCH_STATE_t);
void FAKE_SWITCHES_neg_set_state(SWITCH_STATE_t);
void FAKE_SWITCHES_p_set_state(SWITCH_STATE_t);
void FAKE_SWITCHES_update();

#endif // FAKE_SWITCHES_H_INCLUDED
