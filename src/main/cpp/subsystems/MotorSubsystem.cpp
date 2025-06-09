#include "subsystems/MotorSubsystem.h"
#include "Constants.h"
#include <cmath>
#include <frc/DriverStation.h>

MotorSubsystem::MotorSubsystem()
    : m_motor{MotorConstants::kMotorPWMPin},
      m_encoder{MotorConstants::kEncoderChannelA,
                MotorConstants::kEncoderChannelB} {
  m_encoder.SetDistancePerPulse(1.0);
}

double MotorSubsystem::GetEncoderPosition() const {
  return m_encoder.GetDistance();
}

void MotorSubsystem::ResetEncoder() {
  m_encoder.Reset();
}

void MotorSubsystem::MoveToAngle(double angleDeg, double speedPercent) {
  double error = angleDeg - GetEncoderPosition();
  double speed = std::clamp(speedPercent, -1.0, 1.0);
  double output = std::copysign(speed, error);
  m_motor.Set(output);
  if (std::abs(speedPercent) > 1.0) {
    frc::DriverStation::ReportWarning("Speed percent out of range; clamped");
  }
}

void MotorSubsystem::StopMotor() {
  m_motor.StopMotor();
}
double MotorSubsystem::GetCurrentDraw() const {
  return m_pdp.GetCurrent(MotorConstants::kPDPChannel);
}
