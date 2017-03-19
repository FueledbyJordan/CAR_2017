#ifndef DIST_SENSORS_H
#define DIST_SENSORS_H

#include "Arduino.h"
#include "motor_control.h"
#include <DistanceGP2Y0A21YK.h>


class Follower {
    public:
        enum Side {
            FRONT_SIDE, LEFT_SIDE, RIGHT_SIDE
        };

        enum Direction {
            FORWARD, REVERSE, LEFT, RIGHT
        };

        void setFrontSensorPair(int left, int right);
        void setRightSensorPair(int front, int rear);
        void setLeftSensorPair(int front, int rear);
        int getLeftDistance();
        int getRightDistance();
        int getFrontDistance();
        void setWallDistance(int cm);
        void setFollowSpeed(int speed);
        void followWall(Follower::Side side, Follower::Direction direction);
        int getSensorDistance(int position);        // positions map clocwise starting at back left with 0 to 5 being back right

    private:
        int distance;
        int followSpeed;
        static const int DIFF_GAIN = 12;
        static const int DIST_GAIN = 5;

        // Corresponding sensor pins. Named as RobotsideSensorside
        DistanceGP2Y0A21YK frontLeft;
        DistanceGP2Y0A21YK frontRight;
        DistanceGP2Y0A21YK leftFront;
        DistanceGP2Y0A21YK leftRear;
        DistanceGP2Y0A21YK rightFront;
        DistanceGP2Y0A21YK rightRear;
};

#endif // DIST_SENSORS_H
