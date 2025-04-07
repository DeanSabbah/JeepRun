#include "explosion.h"

float Explosion::GetDamageAt(const float distance) const {
	// Calculate the damage based on the distance from the explosion center
	if (distance <= radius_) {
		//1 - pow(1.0 - tNorm, 5.0) * pow(2, -10 * tNorm)
		return damage_ * (1.0f - (pow(1.0 - distance / radius_, 5.0) * pow(2, -10 * distance / radius_)));
	}
	return 0.0f;
}