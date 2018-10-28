#include "Physics.hpp"

void updateVelocities(Scene* scene, unsigned int tIndex) {
	Vector4 acceleration;
	unsigned int i, pCount = scene->particles.size();
	Particle* particle;

	for(i = tIndex;i < pCount; i += THREAD_COUNT) {
		particle = scene->particles[i];

		if(particle->fixed) continue;

		acceleration = particle->force * ((double)1.0 / particle->mass);
		particle->velocity += acceleration * TIME_STEP;
	}
}

void updatePositions(Scene* scene, unsigned int tIndex) {
	unsigned int i, pCount = scene->particles.size();
	Particle* particle;

	for(i = tIndex;i < pCount; i += THREAD_COUNT) {
		particle = scene->particles[i];

		if(particle->fixed) continue;

		particle->position += particle->velocity * TIME_STEP;
	}
}
