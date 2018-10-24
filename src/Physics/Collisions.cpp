#include "Physics.hpp"

#define COLLISION 50.0f

void collisionParticleParticle(Scene* scene) {
	// variable delcaration
	Vector4 displacementVector, notMasses, forceAB;
	float displacement,intersection,sumOfRadii,massProd;

	unsigned int i, j;
	unsigned int pCount = scene->particles.size();

	// iterate through each particle
	for (i = 0; i < pCount;++i) {
		Particle* particleA = scene->particles[i];
		// iterate through each particle
		for (j = i+1; j < pCount;++j) {
			Particle* particleB = scene->particles[j];

			// no collisions between bound particles
			if (particleB->hasBuddy(particleA)) continue;

			displacementVector = particleA->displacementTo(particleB);
			displacement = V_magnitude(displacementVector);
			sumOfRadii = (particleA->radius + particleB->radius);
			intersection = sumOfRadii - displacement;

			// no collision
			if (intersection <= 0.0)
				continue;

			float coef = intersection;//std::log(intersection + 1.0);
			coef *= COLLISION * coef;
			// normalize if possible
			massProd = particleB->mass * particleA->mass;
			forceAB = displacementVector * (massProd * coef * (
				(displacement != 0.0 && displacement != -0.0)
				? (1 / (displacement * displacement))
				: 0.0
			));
			particleB->force += forceAB;
			particleA->force += -forceAB;
		}
	}
}
