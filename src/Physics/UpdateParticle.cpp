#include "Physics.hpp"

void updateVelocities(Scene* scene) {
	Vector4 acceleration;
	for(auto& particle : scene->particles) {
		if(particle->fixed) continue;
		// Get accelerations from forces
		acceleration = particle->force * (1 / particle->mass);
		particle->velocity += acceleration * TIME_STEP;
		//particle->velocity *= 0.99;
	}
}

void updatePositions(Scene* scene) {
	for(auto& particle : scene->particles) {
		if(particle->fixed) continue;
		particle->position += particle->velocity * TIME_STEP;
	}
}
