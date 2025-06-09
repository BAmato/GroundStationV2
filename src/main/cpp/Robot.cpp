// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc2/command/CommandScheduler.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/shuffleboard/BuiltInWidgets.h>
#include <cmath>

Robot::Robot() {}

/**
 * This function is called every 20 ms, no matter the mode. Use
 * this for items like diagnostics that you want to run during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
  frc2::CommandScheduler::GetInstance().Run();
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

/**
 * This autonomous runs the autonomous command selected by your {@link
 * RobotContainer} class.
 */
void Robot::AutonomousInit() {
  m_autonomousCommand = m_container.GetAutonomousCommand();

  if (m_autonomousCommand) {
    m_autonomousCommand->Schedule();
  }
}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
  // This makes sure that the autonomous stops running when
  // teleop starts running. If you want the autonomous to
  // continue until interrupted by another command, remove
  // this line or comment it out.
  if (m_autonomousCommand) {
    m_autonomousCommand->Cancel();
  }
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic() {}

/**
 * This function is called periodically during test mode.
 */
void Robot::TestInit() {
  m_container.GetMotorSubsystem().ResetEncoder();
  auto& tab = frc::Shuffleboard::GetTab("Test");

  m_runEntry =
      tab.Add("Run Motor Test", false)
          .WithWidget(frc::BuiltInWidgets::kToggleButton)
          .GetEntry();
  m_targetEntry =
      tab.Add("Target Angle", 45.0)
          .WithWidget(frc::BuiltInWidgets::kTextView)
          .GetEntry();
  m_speedEntry =
      tab.Add("Motor Speed %", 0.1)
          .WithWidget(frc::BuiltInWidgets::kTextView)
          .GetEntry();
  m_encoderEntry =
      tab.Add("Antenna Encoder", 0.0)
          .WithWidget(frc::BuiltInWidgets::kNumberBar)
          .GetEntry();
}

void Robot::TestPeriodic() {
  double pos = m_container.GetMotorSubsystem().GetEncoderPosition();
  m_encoderEntry.SetDouble(pos);

  bool run = m_runEntry.GetBoolean(false);
  double target = m_targetEntry.GetDouble(45.0);
  double speed = m_speedEntry.GetDouble(0.1);

  if (run) {
    if (std::abs(target - pos) <= 1.0) {
      m_container.GetMotorSubsystem().StopMotor();
    } else {
      m_container.GetMotorSubsystem().MoveToAngle(target, speed);
    }
  } else {
    m_container.GetMotorSubsystem().StopMotor();
  }
}

/**
 * This function is called once when the robot is first started up.
 */
void Robot::SimulationInit() {}

/**
 * This function is called periodically whilst in simulation.
 */
void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
