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

void oneBall(){ //put one ball in the goal (used at the start of every round)
    rollers.moveRelative(5, 200); //test max velocity and number of rotations needed
    pros::delay(100);
}

void leftAuton(){ //note, measurements are approximate and therefore can be tweaked if we need to get closer
    intakeController->setTarget(720); //intake two balls
    rollersController->setTarget(3600); //output one ball
    
    autChassis->moveDistance(-24.25_in); //back up
    rollersController->setTarget(3600); //eject opposing ball
    rollersController->waitUntilSettled();
    autChassis->turnAngle(180_deg); //turn around
    autChassis->moveDistance(24.25_in); //finish leg 1
    autChassis->turnAngle(-90_deg);
    autChassis->moveDistanceAsync(51.8_in); //finish leg 2
    intakeController->setTarget(36000); //test rotations, idk
    rollersController->setTarget(36000); //test rotations, idk
}