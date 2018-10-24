#include "Physics.hpp"

#define DAMP 0.1f

void forceGravity(Scene* scene) {
	for (auto& particle : scene->particles)
		particle->force[1] += particle->mass * scene->globalGravity;
}

void* t_forceBinding(void* t_data);

void forceBinding(Scene* scene) {
	unsigned int i;
	pthread_t tids[THREAD_COUNT];
	ThreadData tds[THREAD_COUNT];
	for(i = 0;i < THREAD_COUNT;++i)
		tds[i] = { scene, i };
	for(i = 0;i < THREAD_COUNT;++i)
		pthread_create(
			tids + i,
			NULL,
			t_forceBinding,
			tds + i
		);
	for(i = 0;i < THREAD_COUNT;++i)
		pthread_join(tids[i],NULL);
}

void* t_forceBinding(void* t_data) {

	ThreadData* tData = (ThreadData*)t_data;

	Vector4 currDisplacement, unitDisplacement, springForce;
	float currDistance;
	unsigned int bCount = tData->scene->bindings.size();
	Binding* binding;

	for(unsigned int i = tData->index; i < bCount; i += THREAD_COUNT) {
		binding = tData->scene->bindings[i];

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

	pthread_exit(NULL);
}
