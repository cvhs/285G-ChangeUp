#include "devices.hpp" //deleted main.h, might bring it back

okapi::ChassisScales scales(4_in, 11.5_in); //I need to get measurement for wheelbase width

okapi::MotorGroup intake = MotorGroup({/*Insert Intake motorports here*/});
okapi::MotorGroup rollers = MotorGroup({/*Insert rollers motorports here*/});

okapi::Controller controller;


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

	okapi::ControllerButton blueAuton = okapi::controllerDigital::R1;
	okapi::ControllerButton redAuton = okapi::controllerDigital::L1;

	pros::lcd::set_text(1, "Set 285G Auton"); //Change auton based on which color we are
	pros::lcd::set_text(2, "L1 is Red, no input is blue")

	bool autonRed;

	if(redAuton.changedToPressed()){ //For when we have more than 1 auton mode
		autonRed = true;
	}
	else {
		autonRed = false;
	}
}

void autonomous() {
	std::shared_ptr<okapi::OdomChassisController> chassis = okapi::ChassisControllerBuilder().withMotors({1,-2},{11,-12}).withDimensions(okapi::AbstractMotor::gearset::green, scales, imev5GreenTPR).withOdometry(okapi::StateMode::CARTESIAN, 0_mm, 0_deg, 0.0001_mps).buildOdometry(); 
	std::shared_ptr<okapi::ChassisModel> model = std::dynamic_pointer_cast<okapi::ChassisModel>(chassis->getModel());
	pros::delay(1000);

	if(autonRed == true) {
		intake.moveVelocity(150);
		rollers.moveVelocity(120);
		chassis -> setState(/*Red default position here*/);
		chassis -> driveToPoint({1_ft, 1_ft, false, 1_ft});
	}
	else{
		intake.moveVelocity(150);
		rollers.moveVelocity(120);
		chassis -> setState(/*Blue default position here*/);
		chassis -> driveToPoint({7_ft, 7_ft, false, 1_ft});
	}
	}


void opcontrol(){
	//Button inputs
okapi::ControllerButton intakeButton = okapi::ControllerDigital::R2;
okapi::ControllerButton outtakeButton = okapi::ControllerDigital::R1;

std::shared_ptr<okapi::OdomChassisController> chassis = okapi::ChassisControllerBuilder().withMotors({1,-2},{11,-12}).withDimensions(okapi::AbstractMotor::gearset::green, scales, imev5GreenTPR).withOdometry(okapi::StateMode::CARTESIAN, 0_mm, 0_deg, 0.0001_mps).buildOdometry(); 
std::shared_ptr<okapi::ChassisModel> model = std::dynamic_pointer_cast<okapi::ChassisModel>(chassis->getModel());
	
	while(1){

		std::shared_ptr<ChassisController> drive-> model->arcade(controller.getAnalog(okapi::ControllerAnalog::leftY), controller.getAnalog(okapi::ControllerAnalog::leftX)); //arcade style movement
		

		if(intakeButton.isPressed()){
			intake.moveVelocity(150); //Test motor velocities
			rollers.moveVelocity(120);
		}
		else if(outtakeButton.isPressed()){
			intake.moveVelocity(-90); //More testing here, too
			rollers.moveVelocity(-50); //test
		}
		else {
			intake.moveVelocity(0);
			rollers.moveVelocity(0);
		}
		pros::delay(10); //edit delay as we see fit.
	}
}

//outdated PROS opcontrol

/*pros::Controller master(pros::E_CONTROLLER_MASTER);

	pros::Motor left_mtr(1);
	pros::Motor right_mtr(2);

	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_Y);

void opcontrol() {
		left_mtr = left;
		right_mtr = right;
		pros::delay(20);
	}
}
*/
