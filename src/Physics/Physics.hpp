#ifndef PHYSICS_H
#define PHYSICS_H

#include <pthread.h>

#define THREAD_COUNT 4

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

// Particles of radius > 0.0 and particles of radius > 0.0
void collisionSphereSphere(Scene* scene, unsigned int tIndex);
// Particles of radius > 0.0 and triangulated mesh
void collisionSphereMesh(Scene* scene, unsigned int tIndex);

//----------------------------------------------------------------------------//
// Update Particle //
//----------------------------------------------------------------------------//

void updateVelocities(Scene* scene, unsigned int tIndex);
void updatePositions(Scene* scene, unsigned int tIndex);

#endif
