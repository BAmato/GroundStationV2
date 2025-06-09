#pragma once

#include <frc/motorcontrol/Spark.h>
#include <frc/PowerDistribution.h>
#include <frc/Encoder.h>
#include <frc2/command/SubsystemBase.h>

class MotorSubsystem : public frc2::SubsystemBase {
 public:
  MotorSubsystem();

  double GetEncoderPosition() const;
  void ResetEncoder();
  void MoveToAngle(double angleDeg, double speedPercent);
  void StopMotor();
  double GetCurrentDraw() const;

 private:
  frc::Spark m_motor;
  frc::Encoder m_encoder;
  frc::PowerDistribution m_pdp{1, frc::PowerDistribution::ModuleType::kCTRE};
};
