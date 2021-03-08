#include "main.h"
#include "devices.hpp"

bool tankDrive = false;

okapi::ChassisScales scales({4_in, 11.5_in}, imev5GreenTPR);

okapi::MotorGroup intake = MotorGroup({-5,7});
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

void autonomous() {
	//chassis
	 std::shared_ptr<okapi::OdomChassisController> chassis = okapi::ChassisControllerBuilder().withMotors({1,19},{-2,-17}).withDimensions(okapi::AbstractMotor::gearset::green, scales).withOdometry(scales).buildOdometry();
	 std::shared_ptr<okapi::ChassisModel> model = std::dynamic_pointer_cast<okapi::ChassisModel>(chassis->getModel());
	 pros::delay(500);
	 intake.moveVelocity(650); //intake preload
	 pros::lcd::print(0, "Motors working: %f\n", rollers.getActualVelocity()); // print motors
	 chassis->moveDistance(1_ft);
	 chassis->turnAngle(90_deg);
	 chassis->moveDistance(1_ft);
	 rollers.moveVelocity(200); //shoot preload and other ball into goal
}

void opcontrol()
{
	okapi::Controller controller;
	//Button inputs
	okapi::ControllerButton intakeButton(okapi::ControllerDigital::R2, false);
	okapi::ControllerButton outtakeButton(okapi::ControllerDigital::R1, false);
	//declare chassis
	std::shared_ptr<okapi::OdomChassisController> drive = okapi::ChassisControllerBuilder().withMotors({1,19},{-2,-17}).withDimensions(okapi::AbstractMotor::gearset::green, scales).withOdometry(scales).buildOdometry();
	std::shared_ptr<okapi::ChassisModel> model = std::dynamic_pointer_cast<okapi::ChassisModel>(drive->getModel());

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
			 rollers.moveVelocity(200); //Test motor voltages
			 rollers.moveVelocity(200);
			
		}
		else if(outtakeButton.isPressed()){
			 rollers.moveVelocity(-200); //More testing here, too
			 rollers.moveVelocity(-200); //test
			
		}
		else {
			 rollers.moveVelocity(0);
			 rollers.moveVelocity(0);
			
		}
		pros::delay(10); //edit delay as we see fit.
	}
}
