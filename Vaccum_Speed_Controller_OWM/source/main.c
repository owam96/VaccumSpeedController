#include <stdio.h>
#include <stdlib.h>
#include "speed_controller/speed_controller.h"
#include "../test/speed_controller_test/speed_controller_test.h"
#include "../test/fake_motor/fake_motor.h"
#include "switches/switches.h"
#include "../test/fake_switches/fake_switches.h"
#include "motor/motor.h"

#include "../test/unity/unity_fixture.h"

#define MAKE_UNITY_VERBOSE	argc = 2; argv[1] = "-v"

/*!
* \author Omar Walid Mostafa
* \version 1.0
* \date 19/04/2021
* \mainpage Vacuum Speed Controller
*/

void RunAllTests(){
    RUN_TEST_GROUP(SpeedLevel);
    RUN_TEST_GROUP(Motor);
    SPEED_CONTROLLER_run_text_file_tests();
}

int main(int argc, char * argv[])
{
    MAKE_UNITY_VERBOSE;
    UnityMain(argc, argv, RunAllTests);

    printf("\nApp is running...\n");

    SWITCHES_init();
    SPEED_CONTROLLER_init();
    MOTOR_init();

    while(1){

    }
}

