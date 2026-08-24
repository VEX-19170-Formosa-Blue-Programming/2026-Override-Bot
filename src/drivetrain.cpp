// Arcade control scheme
#include "drivetrain.h"
#include "globals.h"

void arcade_drive_offset(float dir, float turn) {
	
	left_mg.move(dir - turn);    // Sets left motor voltage
	right_mg.move(dir + turn);   // Sets motor voltage

}