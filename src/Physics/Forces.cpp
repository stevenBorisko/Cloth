#include "Physics.hpp"

#define DAMP (double)0.1

void forceGravity(Scene* scene, unsigned int tIndex) {

	unsigned int i;
	unsigned int pCount = scene->particles.size();
	Particle* particle;

	for(i = tIndex; i < pCount; i += THREAD_COUNT) {
		particle = scene->particles[i];
		particle->force[1] += particle->mass * scene->globalGravity;
	}
}

void forceBinding(Scene* scene, unsigned int tIndex) {

	Vector4 currDisplacement, unitDisplacement, springForce;
	Vector4 dampingForce[2];

	double currDistance;
	unsigned int i;
	unsigned int bCount = scene->bindings.size();
	Binding* binding;

	for(i = tIndex; i < bCount; i += THREAD_COUNT) {
		binding = scene->bindings[i];

		if(!binding->dynamic) continue;

		currDisplacement = binding->getDisplacement();
		currDistance = V_magnitude(currDisplacement);
		binding->errDistance = currDistance - binding->restDistance;
		if(binding->errDistance <= 0.0) continue;

		unitDisplacement = currDisplacement * (1 / currDistance);
		springForce =
			unitDisplacement
			* (binding->springConstant * binding->errDistance);

		// TODO - Race condition here
		dampingForce[0] = (
			unitDisplacement
			* V_dot(-binding->buddies[0]->velocity, unitDisplacement)
			* DAMP
		);
		dampingForce[1] = (
			-unitDisplacement
			* V_dot(-binding->buddies[1]->velocity, -unitDisplacement)
			* DAMP
		);
		binding->buddies[0]->addForce(springForce + dampingForce[0]);
		binding->buddies[1]->addForce(-springForce + dampingForce[1]);

		if (binding->errDistance >= binding->restDistance) {
			static unsigned long long counter = 0;
			double stretch = (binding->errDistance / binding->restDistance) - 1.0;
			binding->addDistance(binding->restDistance * stretch * TIME_STEP * 10.0);
		}

	}

}
