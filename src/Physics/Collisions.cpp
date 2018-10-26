#include "Physics.hpp"

#define COLLISION 50.0f

void collisionParticleParticle(Scene* scene, unsigned int tIndex) {

	// variable delcaration
	Vector4 displacementVector, notMasses, forceAB;
	double displacement,intersection,sumOfRadii,massProd;

	unsigned int i, j;
	unsigned int pCount = scene->particles.size();
	bool APoint;

	// iterate through each particle
	for (i = tIndex; i < pCount;i += THREAD_COUNT) {

		Particle* particleA = scene->particles[i];
		if(particleA->radius == 0.0 || particleA->radius == -0.0)
			continue;
		// iterate through each particle
		for (j = i+1; j < pCount;++j) {
			Particle* particleB = scene->particles[j];

			if(particleB->radius == 0.0 || particleB->radius == -0.0)
				continue;

			// no collisions between bound particles
			if (particleB->hasBuddy(particleA)) continue;

			displacementVector = particleA->displacementTo(particleB);
			displacement = V_magnitude(displacementVector);

			if(displacement == 0.0 || displacement == -0.0) continue;

			sumOfRadii = (particleA->radius + particleB->radius);
			intersection = sumOfRadii - displacement;

			// no collision
			if (intersection <= 0.0)
				continue;

			double coef = intersection;//std::log(intersection + 1.0);
			coef *= COLLISION * coef;
			// normalize if possible
			massProd = particleB->mass * particleA->mass;
			forceAB = displacementVector * (
				massProd
				* coef
				* (1 / (displacement * displacement))
			);

			particleB->addForce(forceAB);
			particleA->addForce(-forceAB);
		}
	}
}
