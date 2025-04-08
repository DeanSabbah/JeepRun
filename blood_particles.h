#ifndef BLOOD_PARTICLES_H_
#define BLOOD_PARTICLES_H_

#include "particles.h"

namespace game {

    // A set of particles that can be rendered
    class BloodParticles : public Particles {

        public:
            BloodParticles(void);
			// Create the geometry (called once)
			void CreateGeometry(int num_particles) override;
			// Use the geometry

    }; // class BloodParticles
} // namespace game

#endif // BLOOD_PARTICLES_H_
