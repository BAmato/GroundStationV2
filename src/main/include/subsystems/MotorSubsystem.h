#pragma once

#include <frc/PWMVictorSPX.h>
#include <frc/Encoder.h>
#include <frc2/command/SubsystemBase.h>

class MotorSubsystem : public frc2::SubsystemBase {
 public:
  MotorSubsystem();

  double GetEncoderPosition() const;
  void ResetEncoder();

 private:
  frc::PWMVictorSPX m_motor;
  frc::Encoder m_encoder;
};
