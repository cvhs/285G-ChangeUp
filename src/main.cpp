#include "main.h"
#include "comp/devices.hpp"
#include "comp/autonUtils.hpp"

bool tankDrive = false;

void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}


void disabled() {}

void competition_initialize() {

	pros::lcd::initialize();
 //setting the auton when we have different autons
	okapi::ControllerButton blueAuton = okapi::ControllerDigital::R1;
	okapi::ControllerButton redAuton = okapi::ControllerDigital::L1;

	pros::lcd::set_text(1, "Set 285G Auton"); //Change auton based on which color we are
	pros::lcd::set_text(2, "L1 is Red, no input is blue");
/*
	if(redAuton.changedToPressed()){ //For when we have more than 1 auton mode
		autonRed = true;
	}
	else {
		autonRed = false;
	}
	*/
}

/*
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

void autonomous() {
	deploy();

	// leftAuton();

	//rightAuton();

	rightAuton2();


	/*
	//chassis
	 pros::delay(500);
	 intake.moveVelocity(650); //intake preload
	 pros::lcd::print(0, "Motors working: %f\n", rollers.getActualVelocity()); // print motors
	 autChassis->moveDistance(46_in);
	 autChassis->turnAngle(45_deg);
	 autChassis->moveDistance(65.1_in);
	 rollers.moveVelocity(200); //shoot preload and other ball into goal
	*/
}

void opcontrol()
{
	while(1){
		if(tankDrive == true){
			drive->getModel()->tank(controller.getAnalog(ControllerAnalog::leftY), controller.getAnalog(ControllerAnalog::rightY));
			//up-down movement of joysticks read to different directions of movement.
		}
		else{
				drive->getModel()->arcade(controller.getAnalog(ControllerAnalog::leftY), controller.getAnalog(ControllerAnalog::leftX));
				//arcade control - only one joystick controls which way the robot is moving
			}

		if(intakeButton.isPressed()){
			 intake.moveVelocity(200); //Test motor voltages
			 rollers.moveVelocity(550);
		}
		else if(outtakeButton.isPressed()){
			 intake.moveVelocity(-200); //More testing here, too
			 rollers.moveVelocity(-550);
		}
		else if(rollersInButton.isPressed()){
			rollers.moveVelocity(550);
		}
		else if(rollersOutButton.isPressed()){
			rollers.moveVelocity(-550);
		}
		else {
			 intake.moveVelocity(0);
			 rollers.moveVelocity(0);

		}
		pros::delay(10); //edit delay as we see fit.
	}
}
