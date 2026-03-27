# GroundStationV2 NetworkTables Dataflow (Current Implementation)

This document explains how data moves in the **current codebase** and what you should expect to see in **Glass / NetworkTables**.

---

## 1) High-level dataflow

1. `main()` starts `frc::StartRobot<Robot>()`.
2. `Robot` owns `RobotContainer`, which owns `MotorSubsystem`.
3. `RobotPeriodic()` runs every 20 ms and executes `CommandScheduler`.
4. **NetworkTables publishers are only created in `TestInit()`** using Shuffleboard entries on tab `Test`.
5. `TestPeriodic()` updates telemetry entries (`Antenna Encoder`, `Motor Current`) and reads command entries (`Run Motor Test`, `Target Angle`, `Motor Speed %`) to decide whether to move or stop the motor.

Important consequence: if the robot is in Disabled/Auto/Teleop (not Test mode), these Test-tab values are not actively created/updated by this implementation.

---

## 2) Where NetworkTables values come from

The project uses **Shuffleboard widgets** (`tab.Add(...).GetEntry()`) to create `nt::GenericEntry*` publishers/subscribers.

### Created in `Robot::TestInit()` (on tab `Test`)

- `Run Motor Test` (boolean, default `false`) — toggle button
- `Target Angle` (double, default `45.0`) — text view
- `Motor Speed %` (double, default `0.1`) — text view
- `Antenna Encoder` (double, default `0.0`) — number bar
- `Motor Current` (double, default `0.0`) — number bar

### Updated/read in `Robot::TestPeriodic()`

- Writes:
  - `Antenna Encoder = MotorSubsystem::GetEncoderPosition()`
  - `Motor Current = MotorSubsystem::GetCurrentDraw()`
- Reads:
  - `Run Motor Test`
  - `Target Angle`
  - `Motor Speed %`
- Control behavior:
  - If `Run Motor Test == false`: stop motor.
  - If `Run Motor Test == true`: run motor toward target angle until absolute error <= `1.0` degree, then stop.

---

## 3) Expected NetworkTables keys/values in Glass

Because these are created through Shuffleboard tab `Test`, you should expect entries associated with that tab and widget titles.

At minimum, the values and types you should see are:

- `Run Motor Test` → Boolean (`false`/`true`)
- `Target Angle` → Double (degrees, default `45.0`)
- `Motor Speed %` → Double (`-1.0` to `1.0` recommended; code clamps out-of-range inputs)
- `Antenna Encoder` → Double (encoder distance in "degrees" by project assumption)
- `Motor Current` → Double (amps from PDP channel 0)

Notes:
- `Antenna Encoder` uses encoder distance with `distancePerPulse = 1.0`, so numeric value equals pulse count unless gearing/scaling is adjusted.
- `Motor Current` is read from `PowerDistribution` CAN ID `1`, module type `CTRE`, channel `0`.

---

## 4) Systems that must be operational to see data flow

To see values updating in Glass/NetworkTables, all of the following need to be true:

1. **Robot program is running** on the roboRIO (your deploy actually launched and did not crash).
2. **Driver Station is connected and robot is in Test mode** (this implementation publishes in `TestInit/TestPeriodic`).
3. **NT client is connected to the robot** (Glass connected to the same team/host as the roboRIO).
4. **WPILib NetworkTables server is running on robot code** (normally automatic when robot app runs).
5. **Hardware dependencies for telemetry are present**:
   - Encoder wired to DIO 0/1 for meaningful `Antenna Encoder` updates.
   - PDP/PDH configuration matching `frc::PowerDistribution(1, kCTRE)` for `Motor Current`.

If any of the above is missing, you may still be able to ping the roboRIO but see no useful NetworkTables updates.

---

## 5) Why ping can work while Glass shows no data

`ping` only proves IP connectivity. It does **not** prove:

- Robot user program is running,
- Robot is in Test mode,
- NetworkTables client/server handshake is established,
- Keys are being published in the current robot mode.

In this codebase specifically, the most common reason is: **robot is not in Test mode**, so the Test-tab entries are not being created/updated.

---

## 6) Quick troubleshooting checklist (current implementation)

1. Deploy code and reboot robot.
2. Open Driver Station and confirm code is running (no robot code error).
3. Switch robot to **Test** mode.
4. Open Glass → NetworkTables tree and look for the `Test` tab entries listed above.
5. Toggle `Run Motor Test = true` and confirm:
   - `Antenna Encoder` changes while motor rotates.
   - `Motor Current` changes from near-idle when motor is active.
6. If still empty:
   - Verify Glass is connected to robot IP/team.
   - Verify roboRIO time/network config and firewall rules on driver station laptop.
   - Verify deploy log shows no startup exception.

---

## 7) Implementation limitations to be aware of

- Telemetry publishing is tied to **Test mode only**.
- No explicit always-on publisher in `RobotPeriodic()` for Teleop/Auto.
- Encoder scaling is currently `1.0` per pulse and may not match physical angle unless calibrated.

If you want values visible in all modes, move NT publishing to `RobotPeriodic()` (or subsystem periodic) and keep command inputs mode-appropriate.
