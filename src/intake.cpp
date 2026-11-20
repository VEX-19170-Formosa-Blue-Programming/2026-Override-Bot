#include "intake.h"
#include "globals.h"

#include <algorithm>
#include <cmath>

namespace {

constexpr double ARM_POSITION_TOLERANCE_DEGREES = 5.0;
constexpr int ARM_AUTO_LOWER_POWER = 50;

int limit_lift_power(int power, double position) {
	if (!std::isfinite(position)) {
		return 0;
	}

	const double lower_limit = std::min(
		ARM_GROUND_POSITION_DEGREES, ARM_UPPER_POSITION_DEGREES);
	const double upper_limit = std::max(
		ARM_GROUND_POSITION_DEGREES, ARM_UPPER_POSITION_DEGREES);

	if ((position <= lower_limit && power < 0) ||
		(position >= upper_limit && power > 0)) {
		return 0;
	}
	return power;
}

}  // namespace

bool lift_limits_configured() {
	return std::isfinite(ARM_GROUND_POSITION_DEGREES) &&
		std::isfinite(ARM_UPPER_POSITION_DEGREES) &&
		std::fabs(ARM_GROUND_POSITION_DEGREES - ARM_UPPER_POSITION_DEGREES) >
			2.0 * ARM_POSITION_TOLERANCE_DEGREES;
}

// void control_intake(int power) {
// 	intake.move(power);
// }

void control_lift(int power, bool lower_to_ground) {
	static bool lowering_to_ground = false;

	if (!lift_limits_configured()) {
		lowering_to_ground = false;
		lift.brake();
		return;
	}

	const double position = lift.get_position();
	if (lower_to_ground) {
		lowering_to_ground = true;
	}

	if (power != 0) {
		lowering_to_ground = false;
		const int limited_power = limit_lift_power(power, position);
		if (limited_power == 0) {
			lift.brake();
		} else {
			lift.move(limited_power);
		}
		return;
	}

	if (lowering_to_ground) {
		const double error = ARM_GROUND_POSITION_DEGREES - position;
		if (std::fabs(error) <= ARM_POSITION_TOLERANCE_DEGREES) {
			lowering_to_ground = false;
			lift.brake();
			return;
		}

		const int lower_power = error > 0
			? ARM_AUTO_LOWER_POWER
			: -ARM_AUTO_LOWER_POWER;
		const int limited_power = limit_lift_power(lower_power, position);
		if (limited_power == 0) {
			lowering_to_ground = false;
			lift.brake();
		} else {
			lift.move(limited_power);
		}
		return;
	}

	lift.brake();
}