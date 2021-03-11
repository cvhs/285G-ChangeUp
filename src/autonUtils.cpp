#include "devices/devices.hpp"
/* TODO:
ideal auton notes:
throw preload forwards, take in top two in column
throw out bottom of stack so that only opposing color is left
go backwards
do 180
eject opposing ball
move forward 
turn
go forward, turn on intake(?)
intake ball and two other in tower, expelling only our own alliance's balls
*/
void oneBall(){ //put one ball in the goal (used at the start of every round)
    rollers.moveVelocity(200);
    pros::delay(100);
}

void leftAuton(){
    intake.moveVelocity(100);

}