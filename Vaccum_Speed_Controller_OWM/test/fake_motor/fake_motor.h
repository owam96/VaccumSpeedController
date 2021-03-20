#ifndef FAKE_MOTOR_H_INCLUDED
#define FAKE_MOTOR_H_INCLUDED

int FAKE_MOTOR_get_angle();

extern void (*MOTOR_set_angle)(int);
extern void (*MOTOR_init)();

#endif // FAKE_MOTOR_H_INCLUDED
