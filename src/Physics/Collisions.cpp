#include "Physics.hpp"

#define COLLISION 50.0f

void* t_collisionParticleParticle(void* t_data);

void collisionParticleParticle(Scene* scene) {
	unsigned int i;
	pthread_t tids[THREAD_COUNT];
	ThreadData tds[THREAD_COUNT];
	for(i = 0;i < THREAD_COUNT;++i)
		tds[i] = { scene, i };
	for(i = 0;i < THREAD_COUNT;++i)
		pthread_create(
			tids + i,
			NULL,
			t_collisionParticleParticle,
			tds + i
		);
	for(i = 0;i < THREAD_COUNT;++i)
		pthread_join(tids[i],NULL);
}

void* t_collisionParticleParticle(void* t_data) {
	ThreadData* tData = (ThreadData*)t_data;

	// variable delcaration
	Vector4 displacementVector, notMasses, forceAB;
	float displacement,intersection,sumOfRadii,massProd;

	unsigned int i, j;
	unsigned int pCount = tData->scene->particles.size();
	bool APoint;

	// iterate through each particle
	for (i = tData->index; i < pCount;i += THREAD_COUNT) {
		Particle* particleA = tData->scene->particles[i];
		if(particleA->radius == 0.0 || particleA->radius == -0.0)
			continue;
		// iterate through each particle
		for (j = i+1; j < pCount;++j) {
			Particle* particleB = tData->scene->particles[j];

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

			float coef = intersection;//std::log(intersection + 1.0);
			coef *= COLLISION * coef;
			// normalize if possible
			massProd = particleB->mass * particleA->mass;
			forceAB = displacementVector * (
				massProd
				* coef
				* (1 / (displacement * displacement))
			);
			particleB->force += forceAB;
			particleA->force += -forceAB;
		}
	}
	pthread_exit(NULL);
}
