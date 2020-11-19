#include "main.h"
#include "devices.hpp" //keeping both for now, might delete main.h?


void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}


auto chassis = okapi::ChassisControllerBuilder().withMotors({1,-2},{11,-12}).withOdometry(okapi::StateMode::CARTESIAN, 0_mm, 0_deg, 0.0001_mps).build(); //add appropriate motors
auto model = std::dynamic_pointer_cast<okapi::ChassisModel>(chassis->getModel());

/*
Set motors here (i.e. okapi::motorGroup {x,y})
*/

okapi::Controller controller;

bool toggle = false;

void opcontrol(){
	std::shared_ptr<ChassisController> drive-> model->arcade(controller.getAnalog(okapi::ControllerAnalog::leftY), controller.getAnalog(okapi::ControllerAnalog::leftX)); //arcade style movement
	pros::delay(10); //edit delay as we see fit.
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
