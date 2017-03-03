#include "Follower.h"


void Follower::setFrontSensorPair(int left, int right) {
    frontLeft.begin(left);
    frontRight.begin(right);
}

void Follower::setRightSensorPair(int front, int rear) {
    rightFront.begin(front);
    rightRear.begin(rear);
}

void Follower::setLeftSensorPair(int front, int rear) {
    leftFront.begin(front);
    leftRear.begin(rear);
}

void Follower::setWallDistance(int cm) {
    // Todo: check for valid input
    distance = cm;
}

void Follower::setFollowSpeed(int speed) {
    if (speed >= 255){
        speed = 255;
    }else if (speed <= 0){
        speed = 0;
    }

    followSpeed = speed;
}

int Follower::getLeftDistance() {
    return (leftFront.getDistanceCentimeter() + leftRear.getDistanceCentimeter()) / 2;
}

int Follower::getRightDistance() {
    return (rightFront.getDistanceCentimeter() + rightRear.getDistanceCentimeter()) / 2;
}

int Follower::getFrontDistance() {
    return (frontLeft.getDistanceCentimeter() + frontRight.getDistanceCentimeter()) / 2;
}

int Follower::getSensorDistance(int position) {
    switch (position) {
        case 0:
            return leftRear.getDistanceCentimeter();
        case 1:
            return leftFront.getDistanceCentimeter();
        case 2:
            return frontLeft.getDistanceCentimeter();
        case 3:
            return frontRight.getDistanceCentimeter();
        case 4:
            return rightFront.getDistanceCentimeter();
        case 5:
            return rightRear.getDistanceCentimeter();
        default:
            return -1;
    }
}

void Follower::followWall(Follower::Side side, Follower::Direction direction) {
    int meas1, meas2, theta;
    int diffGain = 0;
    int distGain = 0;
    switch (side) {
        case FRONT_SIDE:
            meas1 = frontLeft.getDistanceCentimeter();
            meas2 = frontRight.getDistanceCentimeter();
            if (LEFT == direction) {
                theta = 270;
            } else if (RIGHT == direction) {
                theta = 90;
            } else {
                return;     // error
            }

            diffGain = 6;
            distGain = DIST_GAIN;
            break;

        case RIGHT_SIDE:
            meas1 = rightFront.getDistanceCentimeter();
            meas2 = rightRear.getDistanceCentimeter();
            if (FORWARD == direction) {
                theta = 0;
            } else if (REVERSE == direction) {
                theta = 180;
            } else {
                return;     // error
            }

            diffGain = DIFF_GAIN;
            distGain = DIST_GAIN;
            break;

        case LEFT_SIDE:
            meas1 = leftFront.getDistanceCentimeter();
            meas2 = leftRear.getDistanceCentimeter();
            if (FORWARD == direction) {
                theta = 0;
            } else if (REVERSE == direction) {
                theta = 180;
            } else {
                return;     // error
            }

            diffGain = DIFF_GAIN;
            distGain = DIST_GAIN;
            break;

        default:
            meas1 = meas2 = theta = 0;  // to supress unitialized warning
            return;     // default case is an error
    }

    int angleError = (meas1 - meas2) * diffGain;
    int distError = (((meas1 + meas2) / 2) - distance) * distGain;
    distError %= 360;
    move(followSpeed, theta + distError, angleError);
}
