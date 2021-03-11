#ifndef PAC_MAN_ARM_H
#define PAC_MAN_ARM_H
#include <Servo.h>
#include <NewPing.h>

/*************************************************************
pac-man-arm class

This class is to work the arm in the pac-man-arm compitition.
*************************************************************/

class pac_man_arm {
public:
    pac_man_arm();
    pac_man_arm(int swivelPin, int armRight, int armLeft,
                int grabRight, int grabLeft, int senseTrig,
                int senseEcho, float sensorDist = 6, float baseHeight = 6);
    pac_man_arm(int sensorDist, int baseHeight);
    ~pac_man_arm();

    // high level functions
    /*
    theta is base of stand and r is distance from bot
    this is meant to point the sensor at a point to search

    returns the distance at that point
    */
    float point(int theta, int r);  

    // pass anlge to point at, distance to ground will always be the same
    void grabBlock(float theta);
    void returnBlock();

    // lower level controls
    void setArmAngle(int val);
    void setBaseAngle(int val);
    void grab();
    void release();

    // utils
    float rad_to_degree(float value);
    float servo_map(float value);
private:
    // important distances
    float sensorDist_, baseHeight_;
    const int ARM_LENGTH = 7;

    // constants
    const int MIN = 0;
    const int MAX = 150;  // = (3000 - MAX_PULSE_WIDTH) / 4

    const int MIN_US = 544;
    const int MAX_US = 3000;

    const int MIN_ANG = 0;
    const int MAX_ANG = 360;

    const float pi = 3.14159265358979;

    // arm angles 
    int arm_angle_;
    int base_angle_;

    // all the children servos
    Servo base_, armR_, armL_, grabR_, grabL_;

    // dummy constants for newPing
    int echoPin_, triggerPin_;
    NewPing* sensor_;

    // block locations on board:
    int currBlock_ = 0;
    int BLOCK_LOCS[6] = {0,0,0,0,0,0};
}; // pac_man_arm

#endif // PAC_MAN_ARM_H