#include <psuedo-tank.h>

psuedoTank::psuedoTank(int pinA1, int pinA2, int PWMA, int pinB1, int pinB2, int PWMB,int STBYpin){
  motor1 = new Motor (pinA1, pinA2, PWMA, 1, STBYpin);
  motor2 = new Motor (pinB1, pinB2, PWMB, 1, STBYpin);
}


void psuedoTank::forward(int speed)
{
	motor1->drive(speed);
	motor2->drive(speed);
}

void psuedoTank::forward()
{
	motor1->drive(DEFAULTSPEED);
	motor2->drive(DEFAULTSPEED);
}


void psuedoTank::back(int speed)
{
	int temp = abs(speed);
	motor1->drive(-temp);
	motor2->drive(-temp);
}

void psuedoTank::back()
{
	motor1->drive(-DEFAULTSPEED);
	motor2->drive(-DEFAULTSPEED);
}

void psuedoTank::left()
{
	int temp = abs(DEFAULTSPEED)/2;
	motor1->drive(-temp);
	motor2->drive(temp);

	delay(DELAY_MS);
	brake();
}


void psuedoTank::right()
{
	int temp = abs(DEFAULTSPEED)/2;
	motor1->drive(temp);
	motor2->drive(-temp);
	
	delay(DELAY_MS);
	brake();
}

void psuedoTank::brake()
{
	motor1->brake();
	motor2->brake();
}