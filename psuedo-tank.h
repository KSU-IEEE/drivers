/******************************************************************************
SparkFun_TB6612.h
TB6612FNG H-Bridge Motor Driver Example code
Michelle @ SparkFun Electronics
8/20/16
https://github.com/sparkfun/SparkFun_TB6612FNG_Arduino_Library
Uses 2 motors to show examples of the functions in the library.  This causes
a robot to do a little 'jig'.  Each movement has an equal and opposite movement
so assuming your motors are balanced the bot should end up at the same place it
started.
Resources:
TB6612 SparkFun Library
Development environment specifics:
Developed on Arduino 1.6.4
Developed with ROB-9457
******************************************************************************/


#ifndef PSUEDO_TANK_H
#define PSUEDO_TANK_H

#include <Arduino.h>
#include <SparkFun_TB6612.h>


//used in some functions so you don't have to send a speed
#define DEFAULTSPEED 255  
#define DELAY_MS 3000
class psuedoTank
{
  public:
    // Constructor. Mainly sets up pins.
	psuedoTank(){};
    psuedoTank(int pinA1, int pinA2, int PWMA, int pinB1, int pinB2, int PWMB,int STBYpin);   
	~psuedoTank(){};   

	//Takes 2 motors and goes forward, if it does not go forward adjust offset 
	//values until it does.  These will also take a negative number and go backwards
	//There is also an optional speed input, if speed is not used, the function will
	//use the DEFAULTSPEED constant.
	void forward(int speed);
	void forward();

	//Similar to forward, will take 2 motors and go backwards.  This will take either
	//a positive or negative number and will go backwards either way.  Once again the
	//speed input is optional and will use DEFAULTSPEED if it is not defined.
	void back(int speed);
	void back();

	//Left and right take 2 motors, and it is important the order they are sent.
	//The left motor should be on the left side of the bot.  These functions
	//also take a speed value
	void left();
	void right();

	//This function takes 2 motors and and brakes them
	void brake();
	
  private:
    //variables for the 2 inputs, PWM input, Offset value, and the Standby pin
	int In1, In2, PWM, Offset,Standby;

	float curr_x, curr_y;
	float target_x, target_y;
	float heading;
	
	//private functions that spin the motor CC and CCW
	void fwd(int speed);
	void rev(int speed);

	// Arduino is dumb, so putting in dummy inputs for initialization
	Motor *motor1, *motor2;
};
#endif