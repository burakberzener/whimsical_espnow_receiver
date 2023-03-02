#ifndef distance
#define distance

/*Pin Defines*/
#define sensorFrontLeftEcho 23
#define sensorFrontLeftTrig 22
#define sensorFrontRightEcho 33
#define sensorFrontRightTrig 25

#define sensorSideLeftEcho 26
#define sensorSideLeftTrig 27
#define sensorSideRightEcho 14
#define sensorSideRightTrig 12

#define sensorBackEcho 19
#define sensorBackTrig 18

#define CRICITAL_DISTANCE 150
#define FRONT_TRIG_SIDE_CTRL 100

#define TURNING_ON_ONE_DELAY 1500
#define TURNING_ON_TWO_DELAY 600
#define FORWARD_DELAY 1000
#define BACKWARD_DELAY 500

void initDistance();
int getDistance(int distanceSensorTrig, int distanceSensorEcho);

#endif