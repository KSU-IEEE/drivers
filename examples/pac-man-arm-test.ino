#include <pac-man-arm.h>

pac_man_arm arm = pac_man_arm();

void setup() {
  // put your setup code here, to run once:
  // everything else happens in the libraries
}

void loop() {
  // put your main code here, to run repeatedly:
  float dist = arm.point(75, 12);// point the sensor at a point
  Serial.print(dist);

  arm.grabBlock(180);
  arm.returnBlock();


  while(true) {
    
  }
}
