#ifndef PHYSICS_H
#define PHYSICS_H

#include <pthread.h>

#define TIME_STEP ((double)1.0 / (double)1024.0)
#define THREAD_COUNT 8

#include "../DataStructures/Scene/Scene.hpp"

//----------------------------------------------------------------------------//
// Threads //
//----------------------------------------------------------------------------//

struct ThreadData {
	Scene* scene;
	unsigned int index;
};

void t_execute(void* (*t_func)(void*), ThreadData tds[THREAD_COUNT]);

//----------------------------------------------------------------------------//
// Forces //
//----------------------------------------------------------------------------//

void forceGravity(Scene* scene, unsigned int tIndex);
void forceBinding(Scene* scene, unsigned int tIndex);

//----------------------------------------------------------------------------//
// Collision //
//----------------------------------------------------------------------------//

void collisionParticleParticle(Scene* scene, unsigned int tIndex);

//----------------------------------------------------------------------------//
// Update Particle //
//----------------------------------------------------------------------------//

void updatePositions(Scene* scene, unsigned int tIndex);

#endif
