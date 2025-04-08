#include "explosion.h"

float Explosion::GetDamageAt(const float distance) const {
    if (distance <= radius_) {
        float normalized_distance = distance / radius_; // Normalize distance to [0, 1]
        float linear_dropoff = 1.0f - normalized_distance; // Linearly decrease from 1 to 0
        return damage_ * linear_dropoff; // Scale damage by the dropoff
    }
    return 0.0f; // No damage outside the radius
}