#include "Physics.hpp"
#include "../DataStructures/Scene/Scene.hpp"

//----------------------------------------------------------------------------//
// --- Thread Function Declaration --- //
//----------------------------------------------------------------------------//

void* t_forces(void* t_data);
void* t_collisionDetect(void* t_data);
void* t_updateVelocities(void* t_data);
void* t_updatePositions(void* t_data);

//----------------------------------------------------------------------------//
//
// --- src/DataStructures/Scene.hpp --- //
//
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// --- PhysicsEngine Implementation --- //
//----------------------------------------------------------------------------//

void PhysicsEngine::updateScene(Scene* scene) {

	unsigned int i;
	ThreadData tds[THREAD_COUNT];
	std::vector<Collision> collisions;

	for(i = 0;i < THREAD_COUNT;++i)
		tds[i] = { scene, i, std::vector<Collision>() };

	// reset the particles' forces
	for(auto& particle : scene->particles)
		particle->force = Vector4();

	// Forces

	t_execute(t_forces,tds);
	t_execute(t_updateVelocities,tds);

	// reset the particles' forces
	for(auto& particle : scene->particles)
		particle->force = Vector4();

	// Collisions

		// detect collisions
	t_execute(t_collisionDetect,tds);

		// reduce collision data
	for(i = 0;i < THREAD_COUNT;++i) {
		if(tds[i].collisions.size())
			collisions.insert(
				collisions.end(),
				tds[i].collisions.begin(),
				tds[i].collisions.end()
			);
	}
		// handle collisions
	for(auto& collision : collisions) {
		if(collision.triangle == scene->triangles.size())
			collisionSphereSphere(scene,collision);
		else if(collision.particle == scene->particles.size())
			collisionSphereMesh(scene,collision);
		else continue;
	}

	// Update particles

	t_execute(t_updatePositions,tds);

	return;
}

//----------------------------------------------------------------------------//
//
// --- Physics.hpp --- //
//
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// --- Threads --- //
//----------------------------------------------------------------------------//

void t_execute(void* (*t_func)(void*), ThreadData tds[THREAD_COUNT]) {
	unsigned int i;
	pthread_t tids[THREAD_COUNT];
	for(i = 0;i < THREAD_COUNT;++i)
		pthread_create(tids + i, NULL, t_func, tds + i);
	for(i = 0;i < THREAD_COUNT;++i)
		pthread_join(tids[i],NULL);
}

//----------------------------------------------------------------------------//
//
// --- This File --- //
//
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// --- Thread Function Implementation --- //
//----------------------------------------------------------------------------//

void* t_forces(void* t_data) {
	ThreadData* tData = (ThreadData*)t_data;

	forceGravity(tData->scene, tData->index);
	forceBinding(tData->scene, tData->index);

	pthread_exit(NULL);
}

void* t_collisionDetect(void* t_data) {
	ThreadData* tData = (ThreadData*)t_data;

	std::vector<Collision> cSS, cSM;
	cSS = collisionSphereSphere(tData->scene, tData->index);
	cSM = collisionSphereMesh(tData->scene, tData->index);

	tData->collisions.insert(tData->collisions.end(), cSS.begin(), cSS.end());
	tData->collisions.insert(tData->collisions.end(), cSM.begin(), cSM.end());

	pthread_exit(NULL);
}

void* t_updateVelocities(void* t_data) {
	ThreadData* tData = (ThreadData*)t_data;
	updateVelocities(tData->scene, tData->index);
	pthread_exit(NULL);
}

void* t_updatePositions(void* t_data) {
	ThreadData* tData = (ThreadData*)t_data;
	updatePositions(tData->scene, tData->index);
	pthread_exit(NULL);
}

