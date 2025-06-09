#include "subsystems/MotorSubsystem.h"
#include "Constants.h"
#include <cmath>

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
  double output = std::copysign(speedPercent, error);
  m_motor.Set(output);
}

void MotorSubsystem::StopMotor() {
  m_motor.StopMotor();
}
