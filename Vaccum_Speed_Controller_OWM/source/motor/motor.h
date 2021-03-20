#ifndef MOTOR_H_INCLUDED
#define MOTOR_H_INCLUDED

typedef enum {UNINITIALIZED, MIN_SPEED_ANGLE = 140,
                MED_SPEED_ANGLE = 90, MAX_SPEED_ANGLE = 10} MOTOR_ANGLE_t;

void MOTOR_set_angle_real(int);

void MOTOR_init_real();

int MOTOR_get_angle_real();

#endif // MOTOR_H_INCLUDED
