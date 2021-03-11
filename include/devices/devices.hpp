#pragma once
#include "main.h"

extern ChassisScales scales;
extern std::shared_ptr<okapi::OdomChassisController> autChassis;
extern std::shared_ptr<okapi::ChassisModel> model;

extern std::shared_ptr<okapi::OdomChassisController> drive;

extern okapi::ControllerButton intakeButton;
extern okapi::ControllerButton outtakeButton;

extern okapi::MotorGroup intake;
extern okapi::MotorGroup rollers;

extern okapi::Controller controller;

extern bool autonRed;

extern bool tankDrive;