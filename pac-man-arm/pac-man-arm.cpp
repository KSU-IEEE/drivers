#include <pac-man-arm.h>

// inits and deints
/*******************************************************/
pac_man_arm::pac_man_arm() {
    // setup servos 
    grabL_.attach(2, MIN, MAX);
    grabR_.attach(3, MIN, MAX);

    armL_.attach(4, MIN, MAX);
    armR_.attach(5, MIN, MAX);

    base_.attach(6, MIN, MAX);

    // setup sensor
    triggerPin_ = 12;
    echoPin_ = 13;

    sensor_ (triggerPin_, echoPin_);

    sensorDist_ = 6;
    baseHeight_ = 6;
}

pac_man_arm::pac_man_arm(int swivelPin, int armRight, int armLeft,
            int grabRight, int grabLeft, int senseTrig,
            int senseEcho, float sensorDist, float baseHeight) {
    // setup servos
    grabL_.attach(grabLeft);
    grabR_.attach(grabRight);

    armL_.attach(armLeft);
    armR_.attach(armRight);

    base_.attach(swivelPin);

    triggerPin_ = senseTrig;
    echoPin_ = senseEcho;

    sensor_(senseTrig, senseEcho);

    sensorDist_ = sensorDist;
    baseHeight_ = baseHeight;
}

pac_man_arm::pac_man_arm(int sensorDist, int baseHeight) : pac_man_arm() {
    sensorDist_ = sensorDist;
    baseHeight_ = baseHeight;
}

pac_man_arm::~pac_man_arm() {

}

// high level functions - meant to be called externally
/******************************************************/
float pac_man_arm::point(int theta, int r) {
    // pass in a point in polar form and point the sensor at it, return 
    // the value
    // see the OneNote (IEEE Master Notebook / Software / Robot Arm Notes) 
    // for the proof for this function

    // the target angle for the arm to bend to - in degrees
    // theta = -90 + tan^-1(r/h) + cos^-1(R/sqrt(h^2 + r^2))
    float r_over_h = r / baseHeight_;
    float R_over_c = sensorDist_ / (sqrt(baseHeight_*baseHeight_ + r*r));

    float arm_theta = -90 + rad_to_degree(atan(r_over_h) + acos(R_over_c));
    arm_theta = 180 - arm_theta; // need to have it from 0 degree to pass to function
    setArmAngle(theta);
    setArmAngle(arm_theta);

    // wait for everything to move -- 1 second
    delay(1000);

    // get value
    return sensor_(triggerPin_, echoPin_).ping_in();
} 

void pac_man_arm::grabBlock(float theta) {
    // set arm base
    setBaseAngle(theta);
    release();
    // get angle to ground 
    // again see onenote for proof for this
    float arm_angle = acos(ARM_LENGTH / baseHeight_); // angle below horizon 
    setArmAngle(180 + arm_angle);
    grab();
}

void pac_man_arm::returnBlock() {
    // set arm angle to 0
    setArmAngle(0);

    // handfull of places to put the block
    float base_ang = BLOCK_LOCS[currBlock_];
    currBlock_ = (++currBlock_ > 5) ? 0 : currBlock_;

    setBaseAngle(base_ang);
    release();
}

// low level functions
/******************************************************/

// pass in angle in relation to initial starting position
void pac_man_arm::setArmAngle(int val) {
    // I guess I have to map everything *eye roll*
    float right_ang = servo_map(val);
    float left_ang = servo_map(360 - val);

    armR_.write(servo_map(right_ang));
    armL_.write(servo_map(left_ang));
    delay(750);
}

// pass in angle in relation to initial starting angle
void pac_man_arm::setBaseAngle(int val) {
    // I guess I have to map everything *eye roll*
    float new_ang = servo_map(val);
    base_.write(new_ang);
    delay(750);
}

void pac_man_arm::grab() {
    // just put both grabs at middle position
    grabL_.write(90);
    grabR_.write(90);

    delay(750);
}

void pac_man_arm::release() {
    // left and right will be oposite angles
    grabL_.write(0);
    grabR_.write(180);
    delay(750);
}

// utils
/******************************************************/
float pac_man_arm::rad_to_degree(float value) {
    return (value / pi) * 180;
}

float pac_man_arm::servo_map(float value) {
    return map(value, MIN_ANG, MAX_ANG, MIN_US, MAX_US);
}