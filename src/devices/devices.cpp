#include "comp/devices.hpp"

okapi::ChassisScales scales({4_in, 11.5_in}, imev5GreenTPR);

okapi::MotorGroup intake = MotorGroup({-5,7});
okapi::MotorGroup rollers = MotorGroup({3,4});

//stock auton chassis controller, if we don't like either of the changes
//std::shared_ptr<okapi::OdomChassisController> autChassis = okapi::ChassisControllerBuilder().withMotors({1,19},{-2,-17}).withDimensions(okapi::AbstractMotor::gearset::green, scales).withOdometry(scales).buildOdometry();

std::shared_ptr<okapi::ChassisModel> autmodel = std::dynamic_pointer_cast<okapi::ChassisModel>(autChassis->getModel());

//PID (we may want to tune this)
std::shared_ptr<okapi::OdomChassisController> autChassis = okapi::ChassisControllerBuilder().withMotors({1,19},{-2,-17}).withGains({0.001, 0, 0.0001}, {0.001, 0, 0.0001}, {0.001, 0, 0.0001}).withDimensions(okapi::AbstractMotor::gearset::green, scales).withOdometry(scales).buildOdometry();

//The max velocity (we may also want to tune this)
//std::shared_ptr<okapi::OdomChassisController> autChassis = okapi::ChassisControllerBuilder().withMotors({1,19},{-2,-17}).withMaxVelocity(90).withDimensions(okapi::AbstractMotor::gearset::green, scales).withOdometry(scales).buildOdometry();

const double autkP = 0.001;
const double autkI = 0.0001;
const double autkD = 0.0001;

std::shared_ptr<AsyncPositionController<double, double>> intakeController =
  AsyncPosControllerBuilder()
    .withMotor({intake})
    .withGains({autkP, autkI, autkD})
    .withMaxVelocity(200)
    .build();

std::shared_ptr<AsyncPositionController<double, double>> rollersController =
  AsyncPosControllerBuilder()
    .withMotor({rollers}) //not sure if I can hve 2 motorgroups, or even a whole motorgroup
    .withGains({autkP, autkI, autkD})
    .withMaxVelocity(600)
    .build();

okapi::Controller controller;

//Button inputs
okapi::ControllerButton intakeButton(okapi::ControllerDigital::L2, false);
okapi::ControllerButton outtakeButton(okapi::ControllerDigital::L1, false);
okapi::ControllerButton rollersInButton(okapi::ControllerDigital::R1, false);
okapi::ControllerButton rollersOutButton(okapi::ControllerDigital::R2, false);
//declare chassis
std::shared_ptr<okapi::OdomChassisController> drive = okapi::ChassisControllerBuilder().withMotors({1,19},{-2,-17}).withDimensions(okapi::AbstractMotor::gearset::green, scales).withOdometry(scales).buildOdometry();
std::shared_ptr<okapi::ChassisModel> model = std::dynamic_pointer_cast<okapi::ChassisModel>(drive->getModel());
