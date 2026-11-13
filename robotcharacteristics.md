# Robot Characteristics

## Drive Train
- Four 11W motors + Two 5.5W motors Intake:
	- Three motors per side. They rotate to the same direction. **Blue Cartridge**
- `drive_forward_inches` uses encoder-feedback PID to control each side independently. Tune `DRIVE_PID_KP`, `DRIVE_PID_KI`, and `DRIVE_PID_KD` in `src/globals.cpp`; `DRIVE_PID_MAX_POWER` limits its motor command for safer testing. The move stops after it stays within `ROTATE_TOLERANCE` for `DRIVE_PID_SETTLE_TIME_MS` or returns `false` at `DRIVE_PID_TIMEOUT_MS`.
## Intake
- One 5.5W motor OR One 11W motor **Blue Cartridge**
## Pneumatic Clamp
- 5.5w motor: **Red Cartridge**
