#include <stdio.h>
#include <string.h>
#include "speed_controller_test.h"
#include "../../source/speed_controller/speed_controller.h"
#include "../unity/unity_fixture.h"
#include "../fake_switches/fake_switches.h"
#include "../../source/switches/switches.h"
#include "../../source/motor/motor.h"
#include "../fake_motor/fake_motor.h"
#include "../fake_motor/fake_motor_test.h"

/* Variables to store test data acquired from test_data.txt*/
static SPEED_t switchStates[3] = {};
static MOTOR_ANGLE_t initial_motor_angle;
static MOTOR_ANGLE_t expected_motor_angle;
static long long int pPressTimeMS;

TEST_GROUP(SpeedLevel);
TEST_GROUP(GeneralTestCases);

TEST_SETUP(SpeedLevel){
    SPEED_CONTROLLER_init();
}

TEST_SETUP(GeneralTestCases){
    SPEED_CONTROLLER_init();
}



TEST_TEAR_DOWN(SpeedLevel){

}

TEST_TEAR_DOWN(GeneralTestCases){

}

TEST(SpeedLevel, SpeedMedAfterInit){

    /* Doxygen Test Case Description */
    /*!
          * Testing technique used for this test: **EP and BVA**
		  * @param Given : Speed unknown
		  * @param When  : SPEED_CONTROLLER_init() is called
		  * @param Then  : Current speed is medium
	*/

	/* Arrange */
	SPEED_CONTROLLER_set_speed(UNKNOWN);

	/* Act */
    SPEED_CONTROLLER_init();

    /*Assert*/
    LONGS_EQUAL(MED, SPEED_CONTROLLER_get_speed());

}

TEST(SpeedLevel, SpeedIncreaseMinToMedWhen_Pos_Prepressed){

    /* Doxygen Test Case Description */
    /*!
          * Testing technique used for this test: **EP and BVA**
		  * @param Given : Speed is minimum
		  * @param When  : Positive switch is prepressed
		  * @param Then  : Speed is medium
	*/

	/* Arrange */
	SPEED_CONTROLLER_set_speed(MIN);

	/* Act */
    SWITCHES_positive_press();

    /*Assert*/
    LONGS_EQUAL(MED, SPEED_CONTROLLER_get_speed());

}

TEST(SpeedLevel, SpeedIncreaseMedToMaxWhen_Pos_Prepressed){

    /* Doxygen Test Case Description */
    /*!
          * Testing technique used for this test: **EP and BVA**
		  * @param Given : Speed is medium
		  * @param When  : Positive switch is prepressed
		  * @param Then  : Speed is maximum
	*/

	/* Arrange */
	SPEED_CONTROLLER_set_speed(MED);

	/* Act */
    SWITCHES_positive_press();

    /*Assert*/
    LONGS_EQUAL(MAX, SPEED_CONTROLLER_get_speed());

}

TEST(SpeedLevel, SpeedDecreaseMaxToMedWhen_Neg_Prepressed){

    /* Doxygen Test Case Description */
    /*!
          * Testing technique used for this test: **EP and BVA**
		  * @param Given : Speed is maximum
		  * @param When  : Negative switch is prepressed
		  * @param Then  : Speed is medium
	*/

	/* Arrange */
	SPEED_CONTROLLER_set_speed(MAX);

	/* Act */
    SWITCHES_negative_press();

    /*Assert*/
    LONGS_EQUAL(MED, SPEED_CONTROLLER_get_speed());

}

TEST(SpeedLevel, SpeedDecreaseMedToMinWhen_Neg_Prepressed){

    /* Doxygen Test Case Description */
    /*!
          * Testing technique used for this test: **EP and BVA**
		  * @param Given : Speed is medium
		  * @param When  : Negative switch is prepressed
		  * @param Then  : Speed is minimum
	*/

	/* Arrange */
	SPEED_CONTROLLER_set_speed(MED);

	/* Act */
    SWITCHES_negative_press();

    /*Assert*/
    LONGS_EQUAL(MIN, SPEED_CONTROLLER_get_speed());

}

TEST(SpeedLevel, SpeedMax_Pos_PrepressedNoChange){

    /* Doxygen Test Case Description */
    /*!
          * Testing technique used for this test: **EP and BVA**
		  * @param Given : Speed is maximum
		  * @param When  : Positive switch is prepressed
		  * @param Then  : Speed is still maximum
	*/

	/* Arrange */
	SPEED_CONTROLLER_set_speed(MAX);

	/* Act */
    SWITCHES_positive_press();

    /*Assert*/
    LONGS_EQUAL(MAX, SPEED_CONTROLLER_get_speed());

}

TEST(SpeedLevel, SpeedMin_Neg_PrepressedNoChange){

    /* Doxygen Test Case Description */
    /*!
          * * Testing technique used for this test: **EP and BVA**
		  * @param Given : Speed is minimum
		  * @param When  : Negative switch is prepressed
		  * @param Then  : Speed is still minimum
	*/

	/* Arrange */
	SPEED_CONTROLLER_set_speed(MIN);

	/* Act */
    SWITCHES_negative_press();

    /*Assert*/
    LONGS_EQUAL(MIN, SPEED_CONTROLLER_get_speed());

}

TEST(SpeedLevel, SpeedMax_P_isPressed30secsSpeedMed){

    /* Doxygen Test Case Description */
    /*!
          * Testing technique used for this test: **EP and BVA**
		  * @param Given : Speed is maximum
		  * @param When  : P is pressed for 30 seconds
		  * @param Then  : Speed is medium
	*/

	/* Arrange */
	SPEED_CONTROLLER_set_speed(MAX);

	/* Act */
    SWITCHES_p_press(30000);

    /*Assert*/
    LONGS_EQUAL(MED, SPEED_CONTROLLER_get_speed());

}

TEST(SpeedLevel, SpeedMed_P_isPressed30secsSpeedMin){

    /* Doxygen Test Case Description */
    /*!
          * Testing technique used for this test: **EP and BVA**
		  * @param Given : Speed is medium
		  * @param When  : P is pressed for 30 seconds
		  * @param Then  : Speed is minimum
	*/

	/* Arrange */
	SPEED_CONTROLLER_set_speed(MED);

	/* Act */
    SWITCHES_p_press(30000);

    /*Assert*/
    LONGS_EQUAL(MIN, SPEED_CONTROLLER_get_speed());

}

TEST(SpeedLevel, SpeedMin_P_isPressed30secsNoChange){

    /* Doxygen Test Case Description */
    /*!
          * Testing technique used for this test: **EP and BVA**
		  * @param Given : Speed is minimum
		  * @param When  : P is pressed for 30 seconds
		  * @param Then  : Speed is still minimum
	*/

	/* Arrange */
	SPEED_CONTROLLER_set_speed(MIN);

	/* Act */
    SWITCHES_p_press(30000);

    /*Assert*/
    LONGS_EQUAL(MIN, SPEED_CONTROLLER_get_speed());

}

TEST(SpeedLevel, SpeedMax_P_isPressedLessThan30secsNoChange){

    /* Doxygen Test Case Description */
    /*!
          * Testing technique used for this test: **EP and BVA**
		  * @param Given : Speed is maximum
		  * @param When  : P is pressed for less than 30 seconds (10 seconds)
		  * @param Then  : Speed is still maximum
	*/

	/* Arrange */
	SPEED_CONTROLLER_set_speed(MAX);

	/* Act */
    SWITCHES_p_press(15000);

    /*Assert*/
    LONGS_EQUAL(MAX, SPEED_CONTROLLER_get_speed());

}

/* Tests to cover state transition 1-switch coverage */

TEST(SpeedLevel, StartDefMinDefMin){

    /* Doxygen Test Case Description */
    /*!
          *  Testing technique used for this test: **State transition up to 1-switch coverage**
          *
		  * @param Given : Speed is unknown, start state
		  * @param When  : To advance through this branch of the state transition tree,
                           we simulate the following actions in order: initialize speed controller module,
                           press negative, press positive, press negative
		  * @param Then  : Speed is eventually minimum
	*/

	/* Arrange */
	SPEED_CONTROLLER_set_speed(UNKNOWN);

	/* Act */
    SPEED_CONTROLLER_init();
    SWITCHES_negative_press();
    SWITCHES_positive_press();
    SWITCHES_negative_press();

    /*Assert*/
    LONGS_EQUAL(MIN, SPEED_CONTROLLER_get_speed());

}

TEST(SpeedLevel, StartDefMinDefMax){

    /* Doxygen Test Case Description */
    /*!
          *  Testing technique used for this test: **State transition up to 1-switch coverage**
          *
		  * @param Given : Speed is unknown, start state
		  * @param When  : To advance through this branch of the state transition tree,
                           we simulate the following actions in order: initialize speed controller module,
                           press negative, press positive, press positive again
		  * @param Then  : Speed is eventually maximum
	*/

	/* Arrange */
	SPEED_CONTROLLER_set_speed(UNKNOWN);

	/* Act */
    SPEED_CONTROLLER_init();
    SWITCHES_negative_press();
    SWITCHES_positive_press();
    SWITCHES_positive_press();

    /*Assert*/
    LONGS_EQUAL(MAX, SPEED_CONTROLLER_get_speed());

}

TEST(SpeedLevel, StartDefMaxDefMin){

    /* Doxygen Test Case Description */
    /*!
          *  Testing technique used for this test: **State transition up to 1-switch coverage**
          *
		  * @param Given : Speed is unknown, start state
		  * @param When  : To advance through this branch of the state transition tree,
                           we simulate the following actions in order: initialize speed controller module,
                           press positive, press negative, press negative again
		  * @param Then  : Speed is eventually minimum
	*/

	/* Arrange */
	SPEED_CONTROLLER_set_speed(UNKNOWN);

	/* Act */
    SPEED_CONTROLLER_init();
    SWITCHES_positive_press();
    SWITCHES_negative_press();
    SWITCHES_negative_press();

    /*Assert*/
    LONGS_EQUAL(MIN, SPEED_CONTROLLER_get_speed());

}

TEST(SpeedLevel, StartDefMaxDefMax){

    /* Doxygen Test Case Description */
    /*!
          *  Testing technique used for this test: **State transition up to 1-switch coverage**
          *
		  * @param Given : Speed is unknown, start state
		  * @param When  : To advance through this branch of the state transition tree,
                           we simulate the following actions in order: initialize speed controller module,
                           press positive, press negative, press positive
		  * @param Then  : Speed is eventually maximum
	*/

	/* Arrange */
	SPEED_CONTROLLER_set_speed(UNKNOWN);

	/* Act */
    SPEED_CONTROLLER_init();
    SWITCHES_positive_press();
    SWITCHES_negative_press();
    SWITCHES_positive_press();

    /*Assert*/
    LONGS_EQUAL(MAX, SPEED_CONTROLLER_get_speed());


}

TEST(GeneralTestCases, TestCaseDrawnFromTextFile){

    /* Doxygen Test Case Description */
    /*!
		  * @param Given : Initial condition is specified during runtime
		  * @param When  : Action to take is specified during runtime
		  * @param Then  : Expected output is specified during runtime
	*/

	/* Arrange */
	MOTOR_set_angle(initial_motor_angle);

	/* Act */
    FAKE_SWITCHES_pos_set_state(switchStates[POS]);
    FAKE_SWITCHES_neg_set_state(switchStates[NEG]);
    FAKE_SWITCHES_p_set_state(switchStates[P], pPressTimeMS);
    SWITCHES_update();

    /*Assert*/
    FAKE_MOTOR_outputFinalMotorAngle(MOTOR_get_angle());
    LONGS_EQUAL(expected_motor_angle, MOTOR_get_angle());
}

TEST_GROUP_RUNNER(SpeedLevel){

    RUN_TEST_CASE(SpeedLevel, SpeedMedAfterInit);
    RUN_TEST_CASE(SpeedLevel, SpeedIncreaseMinToMedWhen_Pos_Prepressed);
    RUN_TEST_CASE(SpeedLevel, SpeedIncreaseMedToMaxWhen_Pos_Prepressed);
    RUN_TEST_CASE(SpeedLevel, SpeedDecreaseMaxToMedWhen_Neg_Prepressed);
    RUN_TEST_CASE(SpeedLevel, SpeedDecreaseMedToMinWhen_Neg_Prepressed);
    RUN_TEST_CASE(SpeedLevel, SpeedMax_Pos_PrepressedNoChange);
    RUN_TEST_CASE(SpeedLevel, SpeedMin_Neg_PrepressedNoChange);
    RUN_TEST_CASE(SpeedLevel, SpeedMax_P_isPressed30secsSpeedMed);
    RUN_TEST_CASE(SpeedLevel, SpeedMed_P_isPressed30secsSpeedMin);
    RUN_TEST_CASE(SpeedLevel, SpeedMin_P_isPressed30secsNoChange);
    RUN_TEST_CASE(SpeedLevel, SpeedMax_P_isPressedLessThan30secsNoChange);

    /*State transition tests*/
    RUN_TEST_CASE(SpeedLevel, StartDefMinDefMin);
    RUN_TEST_CASE(SpeedLevel, StartDefMinDefMax);
    RUN_TEST_CASE(SpeedLevel, StartDefMaxDefMin);
    RUN_TEST_CASE(SpeedLevel, StartDefMaxDefMax);
}

void SPEED_CONTROLLER_string_to_enum(SWITCH_TYPE_t switch_type, char string[]){

        /* Each element of the array holds the state of either pos, neg or p buttons
         * switchStates[POS] is switchStates[0] which hold the state of pos switch */
        int index = switch_type;

        if(strcmp(string,"PREPRESSED") == 0)
        {
             switchStates[index] = PREPRESSED;
        }
        else if (strcmp(string,"PRESSED") == 0)
        {
            switchStates[index] = PRESSED;
        }
        else if(strcmp(string,"PRERELEASED") == 0)
        {
            switchStates[index] = PRERELEASED;
        }
        else if(strcmp(string,"RELEASED") == 0)
        {
            switchStates[index] = RELEASED;
        }
        else
        {
            printf("Incorrect test data\n");
        }
}

void SPEED_CONTROLLER_run_text_file_tests(){
    FILE* testDataFile = fopen("test_data.txt","r+");
    char pos_switch_state_STR[20];
    char neg_switch_state_STR[20];
    char p_switch_state_STR[20];

    if(testDataFile)
    {
        int test_num = 0;
        int test_count = 0;

        fscanf(testDataFile, "%d\n", &test_num);

        /* Discard header*/
        fscanf(testDataFile, "%*s%*s%*s%*s%*s%*s\n");

        while(test_num--){

            memset(pos_switch_state_STR,0,20);
            memset(neg_switch_state_STR,0,20);
            memset(p_switch_state_STR,0,20);
            fscanf(testDataFile, "%d%s%s%s%d%d\n", &initial_motor_angle, pos_switch_state_STR,
                   neg_switch_state_STR, p_switch_state_STR, &pPressTimeMS, &expected_motor_angle);


        SPEED_CONTROLLER_string_to_enum(POS, pos_switch_state_STR);
        SPEED_CONTROLLER_string_to_enum(NEG, neg_switch_state_STR);
        SPEED_CONTROLLER_string_to_enum(P, p_switch_state_STR);

        RUN_TEST_CASE(GeneralTestCases, TestCaseDrawnFromTextFile);

        ++test_count;

        }

        fclose(testDataFile);
    }
    else
    {
        printf("Failed To open the file.\n");
    }
}
