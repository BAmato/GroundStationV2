#include "subsystems/MotorSubsystem.h"
#include "Constants.h"

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
