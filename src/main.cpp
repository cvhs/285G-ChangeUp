#include "main.h"
#include "devices.hpp" //deleted main.h, might bring it back

okapi::ChassisScales scales({4_in, 11.5_in}, imev5GreenTPR);

okapi::MotorGroup intake = MotorGroup({5,7});
okapi::MotorGroup rollers = MotorGroup({3,4});

bool autonRed;

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
	// std::shared_ptr<okapi::OdomChassisController> chassis = okapi::ChassisControllerBuilder().withMotors({1,-2},{11,-12}).withDimensions(okapi::AbstractMotor::gearset::green, scales).withOdometry(scales).buildOdometry();
	// std::shared_ptr<okapi::ChassisModel> model = std::dynamic_pointer_cast<okapi::ChassisModel>(chassis->getModel());
	// pros::delay(1000);

	if(autonRed == true) {
		intake.moveVelocity(150);
		rollers.moveVelocity(120);
		//chassis -> setState(/*Red default position here*/);
		//chassis -> driveToPoint({1_ft, 1_ft, false, 1_ft});
	}
	else{
		intake.moveVelocity(150);
		rollers.moveVelocity(120);
		//chassis -> setState(/*Blue default position here*/);
		//chassis -> driveToPoint({7_ft, 7_ft, false, 1_ft});

	}
}

void opcontrol()
{
	okapi::Controller controller;
	//Button inputs
okapi::ControllerButton intakeButton(okapi::ControllerDigital::R2, false);
okapi::ControllerButton outtakeButton(okapi::ControllerDigital::R1, false);
pros::Motor intake_left(5);
pros::Motor intake_right(7);
pros::Motor roller_front(4);
pros::Motor roller_back(3);

std::shared_ptr<okapi::OdomChassisController> drive = okapi::ChassisControllerBuilder().withMotors({1,-12},{11,-2}).withDimensions(okapi::AbstractMotor::gearset::green, scales).withOdometry(scales).buildOdometry();
std::shared_ptr<okapi::ChassisModel> model = std::dynamic_pointer_cast<okapi::ChassisModel>(drive->getModel());

	while(1){

		//std::shared_ptr<okapi::ChassisController> drive->getModel()->arcade(controller.getAnalog(okapi::ControllerAnalog::leftY), controller.getAnalog(okapi::ControllerAnalog::leftX));

		drive->getModel()->arcade(controller.getAnalog(ControllerAnalog::leftY),
	                                  controller.getAnalog(ControllerAnalog::leftX));

		if(intakeButton.isPressed()){
			// intake.moveVelocity(160); //Test motor velocities
			// rollers.moveVelocity(120);
			pros::lcd::set_text(3, "Intake button is pressed.");
			intake_left.move_velocity(160);
			intake_right.move_velocity(160);
			roller_front.move_velocity(120);
			roller_back.move_velocity(120);
		}
		else if(outtakeButton.isPressed()){
			// intake.moveVelocity(-90); //More testing here, too
			// rollers.moveVelocity(-50); //test
			pros::lcd::set_text(3, "Outtake button is pressed.");
			intake_left.move_velocity(-90);
			intake_right.move_velocity(-90);
			roller_front.move_velocity(-50);
			roller_back.move_velocity(-50);
		}
		else {
			// intake.moveVelocity(0);
			// rollers.moveVelocity(0);
			pros::lcd::clear_line(3);
			intake_left.move_velocity(0);
			intake_right.move_velocity(0);
			roller_front.move_velocity(0);
			roller_back.move_velocity(0);
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
// #include "main.h"
//
// bool front = false;
// std::string autoColor = "";
//
// void on_right_button() {
// 	front = true;
// 	autoColor = "Red";
// 	pros::lcd::set_text(1, "Front Red Autonomous Initiated");
// }
//
// void on_left_button() {
// 	front = true;
// 	autoColor = "Blue";
// 	pros::lcd::set_text(1, "Front Blue Autonomous Initiated");
// }
//
// void on_center_button() {
//
// 	if (autoColor == "Blue" && front) {
// 	pros::lcd::set_text(1, "Back Blue Autonomous Initiated");
// 	front = false;
// 	} else if (autoColor == "Red" && front) {
// 	pros::lcd::set_text(1, "Back Red Autonomous Initiated");
// 	front = false;
// 	} else if (!front & autoColor != "") {
// 	pros::lcd::set_text(1, "Front " + autoColor + " Autonomous Initiated");
// 	front = true;
// 	} else {
// 	pros::lcd::set_text(1, "Please select a side first");
// 	}
// }
//
// /**
//  * Runs initialization code. This occurs as soon as the program is started.
//  *
//  * All other competition modes are blocked by initialize; it is recommended
//  * to keep execution time for this mode under a few seconds.
//  */
// void initialize() {
// 	pros::lcd::initialize();
// 	pros::lcd::set_text(1, "285X Autonomous Selector");
//
// 	pros::lcd::register_btn0_cb(on_left_button);
// 	pros::lcd::register_btn1_cb(on_center_button);
// 	pros::lcd::register_btn2_cb(on_right_button);
//
// }
//
// /**
//  * Runs while the robot is in the disabled state of Field Management System or
//  * the VEX Competition Switch, following either autonomous or opcontrol. When
//  * the robot is enabled, this task will exit.
//  */
// void disabled() {}
//
// /**
//  * Runs after initialize(), and before autonomous when connected to the Field
//  * Management System or the VEX Competition Switch. This is intended for
//  * competition-specific initialization routines, such as an autonomous selector
//  * on the LCD.
//  *
//  * This task will exit when the robot is enabled and autonomous or opcontrol
//  * starts.
//  */
// void competition_initialize() {}
//
// /**
//  * Runs the user autonomous code. This function will be started in its own task
//  * with the default priority and stack size whenever the robot is enabled via
//  * the Field Management System or the VEX Competition Switch in the autonomous
//  * mode. Alternatively, this function may be called in initialize or opcontrol
//  * for non-competition testing purposes.
//  *
//  * If the robot is disabled or communications is lost, the autonomous task
//  * will be stopped. Re-enabling the robot will restart the task, not re-start it
//  * from where it left off.
//  */
// void autonomous() {
// 	pros::Motor left_wheels (1);
//  pros::Motor right_wheels (11, true);
// 	// if (autoColor == "Red" && front==true) {
// 	// right_wheels.move_relative(1000, 200);
// 	// left_wheels.move_relative(1000, 200);
// 	//
// 	// }
// 	right_wheels.move_velocity(50);
// 	pros::delay(10000);
// }
//
// /**
//  * Runs the operator control code. This function will be started in its own task
//  * with the default priority and stack size whenever the robot is enabled via
//  * the Field Management System or the VEX Competition Switch in the operator
//  * control mode.
//  *
//  * If no competition control is connected, this function will run immediately
//  * following initialize().
//  *
//  * If the robot is disabled or communications is lost, the
//  * operator control task will be stopped. Re-enabling the robot will restart the
//  * task, not resume it from where it left off.
//  */
// void opcontrol() {
// 	pros::Motor left_wheels (1);
//  pros::Motor right_wheels (11, true); // This reverses the motor
//
// 	pros::Motor main_intake (9);
// 	pros::Motor indexer (10);
// 	pros::Motor left_intake (6);
// 	pros::Motor right_intake (20);
// 	pros::ADIAnalogIn line_sensor ('A');
//
//
// 	std::shared_ptr<ChassisController> drive =
// 	ChassisControllerBuilder()
// 	.withMotors(1, -12, 11, 2)
// 	.withDimensions(AbstractMotor::gearset::green, {{4_in, 11.5_in}, imev5GreenTPR})
// 	.build();
//
// 	Controller controller;
//
// 	pros::motor_brake_mode_e_t mode = pros::E_MOTOR_BRAKE_HOLD;
// 	ControllerDigital a_button {17};
// 	ControllerButton button(a_button);
//
// 	ControllerDigital r1 {8};
// 	ControllerButton right1(r1);
//
// 	ControllerDigital r2 {9};
// 	ControllerButton right2(r2);
//
// 	ControllerDigital l1 {DIGITAL_L1};
// 	ControllerButton left1(l1);
//
//  while (true) {
// 	pros::lcd::set_text(2, "Left Motor Temperature: " + std::to_string(int(left_wheels.get_temperature())) + " C");
// 	pros::lcd::set_text(3, "Right Motor Temperature: " + std::to_string(int(right_wheels.get_temperature())) + " C");
// 	pros::lcd::set_text(4, "Battery Temperature: " + std::to_string(int(pros::battery::get_temperature())) + " C");
// 	pros::lcd::set_text(5, "Battery Current: " + std::to_string(pros::battery::get_current()));
// 	pros::lcd::set_text(6, "Line Sensor: " + std::to_string(line_sensor.get_value()));
//
// 	if (right1.isPressed()) {
// 	pros::lcd::set_text(7, "You are holding the button!");
// 	main_intake.move_velocity(-200);
// 	indexer.move_velocity(-600);
// 	left_intake.move_velocity(200);
// 	right_intake.move_velocity(-200);
//
// 	}
// 	else if (right2.isPressed()) {
// 	main_intake.move_velocity(-200);
// 	left_intake.move_velocity(200);
// 	right_intake.move_velocity(-200);
// 	}
// 	else if (left1.isPressed()) {
// 	main_intake.move_velocity(200);
// 	indexer.move_velocity(600);
// 	left_intake.move_velocity(-200);
// 	right_intake.move_velocity(200);
// 	}
// 	else if (button.isPressed()) {
// 	main_intake.move_velocity(-200);
// 	indexer.move_velocity(600);
// 	left_intake.move_velocity(200);
// 	right_intake.move_velocity(-200);
// 	}
//
// 	else {
// 	main_intake.move_velocity(0);
// 	indexer.move_velocity(0);
// 	left_intake.move_velocity(0);
// 	right_intake.move_velocity(0);
// 	}
//
// 	// if (right2.isPressed()) {
// 	// pros::lcd::set_text(7, "You are holding the button!");
// 	// main_intake.move_velocity(50);
// 	// secondary_intake.move_velocity(50);
// 	// } else {
// 	// main_intake.move_velocity(0);
// 	// secondary_intake.move_velocity(0);
// 	// }
//
//
// 	left_wheels.set_brake_mode(mode);
// 	right_wheels.set_brake_mode(mode);
//
// 	drive->getModel()->arcade(controller.getAnalog(ControllerAnalog::leftY),
//  controller.getAnalog(ControllerAnalog::rightX));
//
//  pros::delay(10);
//  }
// }
