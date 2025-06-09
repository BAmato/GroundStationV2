# Ground Station Control

This project uses WPILib + Gradle. Just clone and run:

```bash
./gradlew build
```

Everything will be downloaded and built automatically.

## Test Mode

When running in **Test** mode, the robot resets the antenna encoder and
publishes the current reading to Shuffleboard under the key `Antenna Encoder` in
the `Test` tab. Additional controls allow the motor to be driven to a specific
angle. To use the test mode:

1. Deploy the robot code and select **Test** mode in the driver station.
2. Open Shuffleboard and watch the value labeled `Antenna Encoder` on the `Test`
   tab.
3. (Optional) Set `Run Motor Test` to true to enable motor movement.
4. Adjust `Target Angle` (degrees) and `Motor Speed %` as desired. The motor
   will rotate until the encoder is within 1 degree of the target and then stop.
5. Set `Run Motor Test` to false when finished to keep the motor idle.
