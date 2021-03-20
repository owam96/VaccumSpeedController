#include <stdio.h>
#include "fake_motor_test.h"
#include "../unity/unity_fixture.h"
#include "fake_motor.h"
#include "../../source/motor/motor.h"
#include "../../source/speed_controller/speed_controller.h"

void FAKE_MOTOR_outputFinalMotorAngle(int);

TEST_GROUP(Motor);

TEST_SETUP(Motor){
    FAKE_MOTOR_init();
}

TEST_TEAR_DOWN(Motor){

}

TEST(Motor, MotorAnge140AfterInit){
    /* Doxygen Test Case Description */
    /*!
          *  Testing technique used for this test: *EP and BVA*
          *
		  * @param Given : Motor angle uninitialized
		  * @param When  : FAKE_MOTOR_init() is called
		  * @param Then  : Motor angle is 140
	*/

	/* Arrange */
	FAKE_MOTOR_set_angle(UNINITIALIZED);

	/* Act */
    FAKE_MOTOR_init();

    /*Assert*/
    LONGS_EQUAL(140, FAKE_MOTOR_get_angle());
}

TEST(Motor, SpeedMinMotorAngle140){
    /* Doxygen Test Case Description */
    /*!
          *  Testing technique used for this test: *EP and BVA*
          *
		  * @param Given : Speed is minimum
		  * @param When  : No action
		  * @param Then  : Motor angle is 140
	*/

	/* Arrange */
	SPEED_CONTROLLER_set_speed(MIN);

	/* Act */

    /*Assert*/
    LONGS_EQUAL(140, FAKE_MOTOR_get_angle());
}

TEST(Motor, SpeedMedMotorAngle90){
    /* Doxygen Test Case Description */
    /*!
          *  Testing technique used for this test: *EP and BVA*
          *
		  * @param Given : Speed is medium
		  * @param When  : No action
		  * @param Then  : Motor angle is 90
	*/

	/* Arrange */
	SPEED_CONTROLLER_set_speed(MED);

	/* Act */

    /*Assert*/
    LONGS_EQUAL(90, FAKE_MOTOR_get_angle());
}

TEST(Motor, SpeedMaxMotorAngle10){
    /* Doxygen Test Case Description */
    /*!
          *  Testing technique used for this test: *EP and BVA*
          *
		  * @param Given : Speed is maximum
		  * @param When  : No action
		  * @param Then  : Motor angle is 10
	*/

	/* Arrange */
	SPEED_CONTROLLER_set_speed(MAX);

	/* Act */

    /*Assert*/
    LONGS_EQUAL(10, FAKE_MOTOR_get_angle());
}

TEST_GROUP_RUNNER(Motor){

    RUN_TEST_CASE(Motor, MotorAnge140AfterInit);
    RUN_TEST_CASE(Motor, SpeedMinMotorAngle140);
    RUN_TEST_CASE(Motor, SpeedMedMotorAngle90);
    RUN_TEST_CASE(Motor, SpeedMaxMotorAngle10);
}

/* Function to output final motor angle per test */
void FAKE_MOTOR_outputFinalMotorAngle(int final_motor_angle)
{
    FILE* motorOutputFile = fopen("motor_angles_output.txt","a");

    if(motorOutputFile)
    {
        fprintf(motorOutputFile, "%d\n", final_motor_angle);

        fclose(motorOutputFile);
    }
    else
    {
        printf("Failed to open the file");
    }

}
