#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  HTMotor)
#pragma config(Sensor, S2,     compass,        sensorNone)
#pragma config(Sensor, S3,     light,          sensorNone)
#pragma config(Sensor, S4,     touch,          sensorNone)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     rightFront,    tmotorTetrix, PIDControl, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     elevatorRight, tmotorTetrix, PIDControl, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     leftFront,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     elevatorLeft,  tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     leftRear,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     rightRear,     tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    Basket,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Tele-Operation Mode Code Template
//
// This file contains a template for simplified creation of an tele-op program for an FTC
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "DrivetrainOctagon.c"

#define TOPHAT_SPEED 30
#define SHELFINCREMENT

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of tele-op mode, you may want to perform some initialization on your robot
// and the variables within your program.
//
// In most cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{
  // Place code here to sinitialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

  return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the tele-op robot operation. Customize as appropriate for
// your specific robot.
//
// Game controller / joystick information is sent periodically (about every 50 milliseconds) from
// the FMS (Field Management System) to the robot. Most tele-op programs will follow the following
// logic:
//   1. Loop forever repeating the following actions:
//   2. Get the latest game controller / joystick settings that have been received from the PC.
//   3. Perform appropriate actions based on the joystick + buttons settings. This is usually a
//      simple action:
//      *  Joystick values are usually directly translated into power levels for a motor or
//         position of a servo.
//      *  Buttons are usually used to start/stop a motor or cause a servo to move to a specific
//         position.
//   4. Repeat the loop.
//
// Your program needs to continuously loop because you need to continuously respond to changes in
// the game controller settings.
//
// At the end of the tele-op period, the FMS will autonmatically abort (
// stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void Octodrivetrain()
{
	int y = joystick.joy1_y1;
	int x = joystick.joy1_x1;

    nxtDisplayCenteredTextLine(4, "Tophat %d", joystick.joy1_TopHat);

	if (joy1Btn(6))
    {
 	    rotateClockwise(TOPHAT_SPEED);
    }
    else if (joy1Btn(5))
    {
	    rotateCounterClockwise(TOPHAT_SPEED);
    }
    else if (abs(y) > 10 || abs(x) > 10)
 	{
 		motor[leftFront] = ((x+y)/2);
 		motor[rightFront] = ((x-y)/2);
 		motor[leftRear] = ((y-x)/2);
 		motor[rightRear] = ((-y-x)/2);
 	}
    else if (joystick.joy1_TopHat != -1)
    {
        switch(joystick.joy1_TopHat)
        {
            case 0:
                moveForwardOn(TOPHAT_SPEED);
                break;
            case 2:
                moveSideRightOn(TOPHAT_SPEED);
                break;
            case 4:
                moveBackwardOn(TOPHAT_SPEED);
                break;
            case 6:
                moveSideLeftOn(TOPHAT_SPEED);
                break;
            default:
                break;
        }
    }
    else
    {
        moveForwardOff();
    }
}
void gravitySlide()
{
    if (joy2Btn(5))
	{
		motor[elevatorRight] = 50;
        motor[elevatorLeft] = -50;
    }
    else if (joy2Btn(7))
    {
        //while(SensorValue(touch) == 0)
        //{
            motor[elevatorRight] = -50;
            motor[elevatorLeft] = 50;
        //}
    }
    else
    {
        motor[elevatorRight] = 0;
        motor[elevatorLeft] = 0;
    }
}

task main()
{
    initializeRobot();

    waitForStart();   // wait for start of tele-op phase

    while (true)
    {
		getJoystickSettings(joystick);//Get joystick input
		Octodrivetrain();//call the forwarddrivetrain function
        gravitySlide();
    }
}