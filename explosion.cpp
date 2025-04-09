#include "explosion.h"

float Explosion::GetDamageAt(const float distance) const {
    if (distance <= radius_) {
        return damage_;
    }
    return 0.0f; // No damage outside the radius
}