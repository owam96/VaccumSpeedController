#ifndef FAKE_MOTOR_H_INCLUDED
#define FAKE_MOTOR_H_INCLUDED

extern void (*MOTOR_set_angle)(int);
extern void (*MOTOR_init)();
extern int (*MOTOR_get_angle)();

#endif // FAKE_MOTOR_H_INCLUDED
