#include "Physics.hpp"

#define DAMP 0.1f

void forceGravity(Scene* scene) {
	for (auto& particle : scene->particles)
		particle->force[1] += particle->mass * scene->globalGravity;
}

void forceBinding(Scene* scene) {
	Vector4 currDisplacement, unitDisplacement, springForce;
	float currDistance;

	for(auto& binding : scene->bindings) {

		if(!binding->dynamic) continue;

		currDisplacement = binding->getDisplacement();
		currDistance = V_magnitude(currDisplacement);
		binding->errDistance = currDistance - binding->initDistance;
		if(binding->errDistance <= 0.0) continue;

		if (binding->errDistance >= binding->initDistance) {
			static unsigned long long counter = 0;
			float stretch = (binding->errDistance / binding->initDistance) - 1.0;
			binding->initDistance += binding->initDistance * stretch * TIME_STEP * 10.0;
		}

		unitDisplacement = currDisplacement * (1 / currDistance);
		springForce =
			unitDisplacement
			* (binding->springConstant * binding->errDistance);

		binding->buddies[0]->force += springForce - (unitDisplacement * V_dot(binding->buddies[0]->velocity, unitDisplacement) * DAMP);
		binding->buddies[1]->force += -springForce - (unitDisplacement * V_dot(binding->buddies[1]->velocity, unitDisplacement) * DAMP);
	}
}
