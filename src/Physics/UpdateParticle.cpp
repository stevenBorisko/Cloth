#include "Physics.hpp"

void updatePositions(Scene* scene, unsigned int tIndex) {
	Vector4 acceleration;
	unsigned int i, pCount = scene->particles.size();
	Particle* particle;

	for(i = tIndex;i < pCount; i += THREAD_COUNT) {
		particle = scene->particles[i];

		if(particle->fixed) continue;

		// Get accelerations from forces
		acceleration = particle->force * (1 / particle->mass);
		particle->velocity += acceleration * TIME_STEP;
		particle->position += particle->velocity * TIME_STEP;
	}
}
