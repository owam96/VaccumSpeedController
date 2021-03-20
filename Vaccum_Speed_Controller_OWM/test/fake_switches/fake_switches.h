#include "../../source/switches/switches.h"

#ifndef FAKE_SWITCHES_H_INCLUDED
#define FAKE_SWITCHES_H_INCLUDED

extern void (*SWITCHES_init)();
extern void (*SWITCHES_positive_press)();
extern SWITCH_STATE_t (*SWITCHES_pos_get_state)();
extern void (*SWITCHES_negative_press)();
extern SWITCH_STATE_t (*SWITCHES_neg_get_state)();
extern void (*SWITCHES_p_press)(long long int);
extern SWITCH_STATE_t (*SWITCHES_p_get_state)();
extern void (*SWITCHES_p_release)();



#endif // FAKE_SWITCHES_H_INCLUDED
