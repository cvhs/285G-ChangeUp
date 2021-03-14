#pragma once
#include "main.h"

extern ChassisScales scales;
extern std::shared_ptr<okapi::OdomChassisController> autChassis;
extern std::shared_ptr<okapi::ChassisModel> model;

extern std::shared_ptr<AsyncPositionController<double, double>> intakeController;
extern std::shared_ptr<AsyncPositionController<double, double>> rollersController;

extern std::shared_ptr<okapi::OdomChassisController> drive;

extern okapi::ControllerButton intakeButton;
extern okapi::ControllerButton outtakeButton;
extern okapi::ControllerButton rollersInButton;
extern okapi::ControllerButton rollersOutButton;

extern okapi::MotorGroup intake;
extern okapi::MotorGroup rollers;

extern okapi::Controller controller;

extern bool autonRed;

extern bool tankDrive;
