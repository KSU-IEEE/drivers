#include <SparkFun_TB6612.h>  // yes you have to include both :(
#include "psuedo-tank.h"

int delay_ms = 3000;  // TUNE THIS

/************************************************
 * test-psuedo-tank.ino
 * 
 * Tests the psuedo-tank design. Will drive in a
 * simple box, then reverse and do it all
 ************************************************/
// change these for wahtever the actual hookup is 
int pinA1 = A0;
int pinA2 = A1;
int APWM = 13;

int pinB1 = A3;
int pinB2 = A4;
int BPWM = 12;

int standby = A2;

psuedoTank car(pinA1, pinA2, APWM, pinB1, pinB2, BPWM, standby);

void setup() {
  // put your setup code here, to run once:
  // everything happens in the libraryes
}

void loop() {
  // put your main code here, to run repeatedly:
  // drive forward
  car.forward();
  delay(3000);
  car.brake();

  car.right();

  car.forward();
  delay(3000);
  car.brake();

  // turn 180 degrees
  car.left();
  car.left();

  car.forward();
  delay(3000);
  car.brake();

  car.left();

  car.forward();
  delay(3000);
  car.brake();

  car.right();
  car.right();
}
