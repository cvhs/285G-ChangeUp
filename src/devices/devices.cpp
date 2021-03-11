#include "devices/devices.hpp"

okapi::ChassisScales scales({4_in, 11.5_in}, imev5GreenTPR);

okapi::MotorGroup intake = MotorGroup({-5,7});
okapi::MotorGroup rollers = MotorGroup({3,4});

std::shared_ptr<okapi::OdomChassisController> autChassis = okapi::ChassisControllerBuilder().withMotors({1,19},{-2,-17}).withDimensions(okapi::AbstractMotor::gearset::green, scales).withOdometry(scales).buildOdometry();
//std::shared_ptr<okapi::ChassisModel> model = std::dynamic_pointer_cast<okapi::ChassisModel>(autChassis->getModel());

okapi::Controller controller;

//Button inputs
okapi::ControllerButton intakeButton(okapi::ControllerDigital::R2, false);
okapi::ControllerButton outtakeButton(okapi::ControllerDigital::R1, false);
//declare chassis
std::shared_ptr<okapi::OdomChassisController> drive = okapi::ChassisControllerBuilder().withMotors({1,19},{-2,-17}).withDimensions(okapi::AbstractMotor::gearset::green, scales).withOdometry(scales).buildOdometry();
std::shared_ptr<okapi::ChassisModel> model = std::dynamic_pointer_cast<okapi::ChassisModel>(drive->getModel());
