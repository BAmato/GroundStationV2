// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc2/command/button/Trigger.h>

#include "commands/Autos.h"

MotorSubsystem& RobotContainer::GetMotorSubsystem() { return m_motorSubsystem; }

RobotContainer::RobotContainer() {
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureBindings();
}

void RobotContainer::ConfigureBindings() {
  // Configure your trigger bindings here

}

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  return autos::ExampleAuto();
  // An example command will be run in autonomous

}
