# Ground Station Control

This project uses WPILib + Gradle. Just clone and run:

```bash
./gradlew build
```

Everything will be downloaded and built automatically.

## Encoder Test

When running in **Test** mode, the robot will reset the antenna encoder and
continuously publish the current encoder reading to SmartDashboard under the key
"Antenna Encoder". This allows you to verify encoder wiring and functionality
without commanding the motor. To run the test:

1. Deploy the robot code and select **Test** mode in the driver station.
2. Open SmartDashboard and watch the value labeled `Antenna Encoder`.
3. Manually rotate the antenna; the displayed value should change in degrees.