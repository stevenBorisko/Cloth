#include "Physics.hpp"
#include "../DataStructures/Scene/Scene.hpp"

//----------------------------------------------------------------------------//
// --- Helper Function Declaration --- //
//----------------------------------------------------------------------------//

void* t_forces(void* t_data);
void* t_update(void* t_data);

//----------------------------------------------------------------------------//
// --- PhysicsEngine and Physics Implementation --- //
//----------------------------------------------------------------------------//

void PhysicsEngine::updateScene(Scene* scene, Scene* swap) {

	unsigned int i;
	ThreadData tds[THREAD_COUNT];
	scene->deepCopyInto(swap);

	// reset the particles' forces
	for(auto& particle : scene->particles)
		particle->force = Vector4();

	// forces
	for(i = 0;i < THREAD_COUNT;++i)
		tds[i] = { scene, i };

	t_execute(t_forces,tds);
	t_execute(t_update,tds);

	// update particles
	return;
}

void t_execute(void* (*t_func)(void*), ThreadData tds[THREAD_COUNT]) {
	unsigned int i;
	pthread_t tids[THREAD_COUNT];
	for(i = 0;i < THREAD_COUNT;++i)
		pthread_create(tids + i, NULL, t_func, tds + i);
	for(i = 0;i < THREAD_COUNT;++i)
		pthread_join(tids[i],NULL);
}

//----------------------------------------------------------------------------//
// --- Helper Function Implementation --- //
//----------------------------------------------------------------------------//

void* t_forces(void* t_data) {
	ThreadData* tData = (ThreadData*)t_data;

	forceGravity(tData->scene, tData->index);
	forceBinding(tData->scene, tData->index);

	collisionParticleParticle(tData->scene, tData->index);


	pthread_exit(NULL);
}

void* t_update(void* t_data) {
	ThreadData* tData = (ThreadData*)t_data;
	updatePositions(tData->scene, tData->index);
}
