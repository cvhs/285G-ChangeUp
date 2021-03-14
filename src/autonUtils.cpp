#include "comp/devices.hpp"
/* TODO:
ideal auton notes:
throw preload forwards, take in top two in column
throw out bottom of stack so that only opposing color is left
go backwards
eject opposing ball
do 180
move forward
turn
go forward, turn on intake(?)
intake ball and two other in tower, expelling only our own alliance's balls
*/

void deploy(){
  autChassis->moveDistance(.5_in);
  autChassis->waitUntilSettled();
}

void oneBall(){ //put one ball in the goal (used at the start of every round)
    intakeController->setTarget(36000);
    rollers.moveVelocity(200);
    intakeController->waitUntilSettled();
    rollers.moveVelocity(0);
}

void leftAuton(){ //note, measurements are approximate and therefore can be tweaked if we need to get closer
    intakeController->setTarget(720); //intake two balls
    rollers.moveVelocity(200); //output one ball
    intakeController->waitUntilSettled();
    pros::delay(1000);
    rollers.moveVelocity(0);

    autChassis->moveDistance(-24.25_in); //back up
    rollers.moveVelocity(150);
    intakeController->setTarget(1800); //eject opposing ball
    intakeController->waitUntilSettled();
    rollers.moveVelocity(0);

    autChassis->turnAngle(180_deg); //turn around
    autChassis->moveDistance(24.25_in); //finish leg 1

    autChassis->turnAngle(-90_deg);
    autChassis->moveDistanceAsync(51.8_in); //finish leg 2
    intake.moveVelocity(200); //test rotations, idk
    rollers.moveVelocity(200); //test rotations, idk
}