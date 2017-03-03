#include "motor_control.h"
#include "robo_comm.h"
#include "Follower.h"
#include <QTRSensors.h>


/*       Constants      */
static const int DEFAULT_SPEED = 100;
static const int ALIGN_THRESH = 15;
static const int NUM_SENSORS = 6;
static const int QTR_TIMEOUT = 2500;  // max wait time (us) for sensor outputs to go low
static const int BLACK_THRESHOLD = 200; // todo: change after testing
static const int TRAIN_GAP_THRESH = 25;
static const int COLOR_UNK = -1;
static const int COLOR_RED = 0;
static const int COLOR_GRN = 1;
static const int COLOR_BLU = 2;
static const int COLOR_YEL = 3;

/*        Globals       */
Follower follower;
QTRSensorsRC qtr((uint8_t []) {32, 30, 28, 26, 24, 22}
                , NUM_SENSORS
                , QTR_TIMEOUT
                , QTR_NO_EMITTER_PIN);

int trainCars[]= { COLOR_UNK, COLOR_UNK, COLOR_UNK, COLOR_UNK };   // initialize order to unknown

/* Function prototypes  */
int getBlock();

void setup() {
    Serial.begin(9600);
    armSetup();

    pinMode(M1DIR, OUTPUT);
    pinMode(M1SPD, OUTPUT);
    pinMode(M2DIR, OUTPUT);
    pinMode(M2SPD, OUTPUT);
    pinMode(M3DIR, OUTPUT);
    pinMode(M3SPD, OUTPUT);
    pinMode(M4DIR, OUTPUT);
    pinMode(M4SPD, OUTPUT);


    follower.setFollowSpeed(80);
    follower.setRightSensorPair(A5, A4);
    follower.setFrontSensorPair(A2, A3);
    follower.setLeftSensorPair(A1, A0);
    follower.setWallDistance(16);
}

void loop() {

    // traverse the first wall
    while (follower.getFrontDistance() > 16) {
        follower.followWall(Follower::RIGHT_SIDE, Follower::FORWARD);
    }

    // stop and calibrate for black
    move(0, 0, 0);
    for (int i = 0; i < 50; i++) {
        qtr.calibrate();
    }

    // move over until over all white
    while (follower.getRightDistance() < 22) {
        follower.followWall(Follower::FRONT_SIDE, Follower::LEFT);
    }
    // stop and calibrate for white
    move(0, 0, 0);
    for (int i = 0; i < 50; i++) {
        qtr.calibrate();
    }

    // move over until over all white
    while (follower.getRightDistance() < 22) {
        follower.followWall(Follower::FRONT_SIDE, Follower::LEFT);
    }
    // stop and calibrate for white
    move(0, 0, 0);
    for (int i = 0; i < 50; i++) {
        qtr.calibrate();
    }

    // Follow wall until: not over white, over white, not over white
    while (overWhite()) {
        follower.followWall(Follower::FRONT_SIDE, Follower::LEFT);
    }
    while (!overWhite()) {
        follower.followWall(Follower::FRONT_SIDE, Follower::LEFT);
    }
    while (overWhite()) {
        follower.followWall(Follower::FRONT_SIDE, Follower::LEFT);
    }
    move(0, 0, 0);
    // at this point, at least 1 qtr is off the white pad

    int currentBlockColor = getBlock();
    while (!getBlock()) {
        // inch over and try again. Change to more robust direction argument
        move(DEFAULT_SPEED, 90, 0);
        delay(500);
        move(0, 0, 0);
        currentBlockColor = getBlock();
    }

    // turn left 90
    move(0, 0, -100);
    delay(700);
    move(0, 0, 0);

    // follow to train cars
    while (follower.getFrontDistance() > 10) {
        follower.followWall(Follower::RIGHT_SIDE, Follower::FORWARD);
    }

    // todo: move arm to color detect position
    for (int trainCar = 0; trainCar < 4; trainCar++) {
        // drive to edge of train car
        while (follower.getSensorDistance(2) < TRAIN_GAP_THRESH) {
            follower.followWall(Follower::FRONT_SIDE, Follower::LEFT);
        }
        if (trainCars[trainCar] == COLOR_UNK) {
            // get the color
            move(0, 0, 0);
            sideStep(DEFAULT_SPEED, 90, 400);
            sendGetCarColor();
            int carColor = COLOR_UNK;

            // wait for message and store color
            while(1) {      // todo change to timeout
                if (hasMessage()) {
                    Operation op = readMessage();
                    if (0 == strcmp(op.cmd, "cc")) {
                        carColor = op.param[0];
                        if (carColor == COLOR_UNK) {
                            sideStep(DEFAULT_SPEED, 90, 400);
                            sendGetCarColor();
                        } else {
                            trainCars[trainCar] = carColor;
                            break;
                        }
                    } else {
                        // unexpected message. Do nothing.
                    }
                }
            }
            if (carColor == currentBlockColor) {
                // dump the block
                break;
            }
        } else if (trainCars[trainCar] == currentBlockColor) {
            move(0, 0, 0);
            sideStep(DEFAULT_SPEED, 90, 400);
            // dump the block
            break;
        } else {
            // car color known and not correct, keep going
        }
    }

    // we're done, stop forever
    while (1) {
        move(0, 0, 0);
    }
}
/* Function searches for and aligns on a block then grips it.
 *  @return integer corresponding to color grabbed or -1 if unable
 */
int getBlock() {
    int x, y, z, color;
    x = y = z = 65535;
    color = -1;
     // tell Pi to get alignment and wait for answer
    while (x > ALIGN_THRESH || y > ALIGN_THRESH || z > ALIGN_THRESH) {
        sendAlign();
        delay(100);
        int lastMessage = millis();
        do {
            if (hasMessage()) {
                lastMessage = millis();       // reset timeout
                Operation op = readMessage();
                // Pi sends the "al"ign signal with x, y and z
                if (0 == strcmp(op.cmd, "al")) {
                    x = op.param[0];
                    y = op.param[1];
                    z = op.param[2];
                    color = op.param[3];
                    align(op.param[0], op.param[1], op.param[2]);
                } else if (0 == strcmp(op.cmd, "no")) {
                    // no qr found
                    return -1;
                } else {
                    // unexpected message: do nothing.
                }
            }
        } while (millis() - lastMessage < 2000);
    } // threshold checking loop

    // todo: grab block

    return color;
}

bool overWhite() {
    unsigned int sensorValues[NUM_SENSORS];
    qtr.readCalibrated(sensorValues, QTR_EMITTERS_OFF);
    bool allWhite = true;
    for (int i = 0; i < NUM_SENSORS; i++) {
        if (sensorValues[i] < BLACK_THRESHOLD) {
            allWhite = false;
            break;
        }
    }
    return allWhite;
}

int getTrainPosition(int color) {
    int pos = COLOR_UNK;
    for (int i = 0; i < 4; i++) {
        if (trainCars[i] == color) {
            pos = i;
            break;
        }
    }
    return pos;
}
