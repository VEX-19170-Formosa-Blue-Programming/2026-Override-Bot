#include "intake.h"
#include "globals.h"

void control_intake(int power) {
	intake.move(power);
}

void control_lift(int power) {
	lift.move(power);
}