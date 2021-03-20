#ifndef SWITCHES_H_INCLUDED
#define SWITCHES_H_INCLUDED

typedef enum {RELEASED, PRESSED, PREPRESSED, PRERELEASED} SWITCH_STATE_t;

typedef enum {POS, NEG, P} SWITCH_TYPE_t;

void SWITCHES_init_real();

extern void (*SWITCHES_init)();
extern void (*SWITCHES_positive_press)();
extern SWITCH_STATE_t (*SWITCHES_pos_get_state)();
extern void (*SWITCHES_negative_press)();
extern SWITCH_STATE_t (*SWITCHES_neg_get_state)();
extern void (*SWITCHES_p_press)(long long int);
extern SWITCH_STATE_t (*SWITCHES_p_get_state)();
extern void (*SWITCHES_p_release)();

#endif // SWITCHES_H_INCLUDED
