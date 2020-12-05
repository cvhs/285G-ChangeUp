#include "main.h"
#include "devices.hpp"

okapi::ChassisScales scales({4_in, 11.5_in}, imev5GreenTPR);

okapi::MotorGroup intake = MotorGroup({5,7});
okapi::MotorGroup rollers = MotorGroup({3,4});


void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

void initialize() {}

void disabled() {}

void competition_initialize() {

	pros::lcd::initialize();

	okapi::ControllerButton blueAuton = okapi::ControllerDigital::R1;
	okapi::ControllerButton redAuton = okapi::ControllerDigital::L1;

	pros::lcd::set_text(1, "Set 285G Auton"); //Change auton based on which color we are
	pros::lcd::set_text(2, "L1 is Red, no input is blue");



	if(redAuton.changedToPressed()){ //For when we have more than 1 auton mode
		autonRed = true;
	}
	else {
		autonRed = false;
	}
}

void autonomous() {
	 std::shared_ptr<okapi::OdomChassisController> chassis = okapi::ChassisControllerBuilder().withMotors({1,19},{-2,-17}).withDimensions(okapi::AbstractMotor::gearset::green, scales).withOdometry(scales).buildOdometry();
	 std::shared_ptr<okapi::ChassisModel> model = std::dynamic_pointer_cast<okapi::ChassisModel>(chassis->getModel());
	 pros::delay(500);
	 intake.moveVelocity(600);
	 chassis->moveDistance(1_ft);
	 chassis->turnAngle(90_deg);
	 chassis->moveDistance(1_ft);
	 rollers.moveVelocity(600);
	 
	 
}

void opcontrol()
{
	okapi::Controller controller;
	//Button inputs
okapi::ControllerButton intakeButton(okapi::ControllerDigital::R2, false);
okapi::ControllerButton outtakeButton(okapi::ControllerDigital::R1, false);

std::shared_ptr<okapi::OdomChassisController> drive = okapi::ChassisControllerBuilder().withMotors({1,19},{-2,-17}).withDimensions(okapi::AbstractMotor::gearset::green, scales).withOdometry(scales).buildOdometry();
std::shared_ptr<okapi::ChassisModel> model = std::dynamic_pointer_cast<okapi::ChassisModel>(drive->getModel());

	while(1){

				drive->getModel()->arcade(controller.getAnalog(ControllerAnalog::leftY),
	                                  controller.getAnalog(ControllerAnalog::leftX));

		if(intakeButton.isPressed()){
			 intake.moveVelocity(600); //Test motor velocities
			 rollers.moveVelocity(600);
			
		}
		else if(outtakeButton.isPressed()){
			 intake.moveVelocity(-200); //More testing here, too
			 rollers.moveVelocity(-200); //test
			
		}
		else {
			 intake.moveVelocity(0);
			 rollers.moveVelocity(0);
			
		}
		pros::delay(10); //edit delay as we see fit.
	}
}


