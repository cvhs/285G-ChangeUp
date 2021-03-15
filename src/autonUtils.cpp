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
    autChassis->moveDistance(45_in);
    pros::delay(500);
    autChassis->turnAngle(-152_deg);
    pros::delay(500);
    intakeController->setTarget(36000);
    autChassis->moveDistance(52_in);
    rollersController->setTarget(36000);
    pros::delay(20000);
    rollers.moveVelocity(0);
    intake.moveVelocity(0);
}

void rightAuton(){
  autChassis->moveDistance(45_in);
  pros::delay(500);
  autChassis->turnAngle(152_deg);
  pros::delay(500);
  intakeController->setTarget(7200);
  autChassis->moveDistance(52_in);
  rollersController->setTarget(3600);
  pros::delay(20000);
  rollers.moveVelocity(0);
  intake.moveVelocity(0);
}
