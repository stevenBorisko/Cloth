#ifndef PHYSICS_H
#define PHYSICS_H

#include <pthread.h>

#define THREAD_COUNT 8

#include "../DataStructures/Scene/Scene.hpp"

//----------------------------------------------------------------------------//
// --- Threads --- //
//----------------------------------------------------------------------------//

struct ThreadData {
	Scene* scene;
	unsigned int index;
	void* data;
};

void t_execute(void* (*t_func)(void*), ThreadData tds[THREAD_COUNT]);

//----------------------------------------------------------------------------//
// --- Struct Definitions --- //
//----------------------------------------------------------------------------//

// make either particle or triangle the size of the list
struct Collision {
	long unsigned int collider, particle, triangle;
	double intersection;
};

//----------------------------------------------------------------------------//
// --- Forces --- //
//----------------------------------------------------------------------------//

void forceGravity(Scene* scene, unsigned int tIndex);
void forceBinding(Scene* scene, unsigned int tIndex);

//----------------------------------------------------------------------------//
// --- Collision Detection --- //
//----------------------------------------------------------------------------//

// Particles of radius > 0.0 and particles of radius > 0.0
std::vector<Collision> collisionSphereSphere(Scene* scene, unsigned int tIndex);
// Particles of radius > 0.0 and triangulated mesh
std::vector<Collision> collisionSphereMesh(Scene* scene, unsigned int tIndex);

//----------------------------------------------------------------------------//
// --- Collision Handling --- //
//----------------------------------------------------------------------------//

void collisionSphereSphere(Scene* scene, const Collision& collision);
void collisionSphereMesh(Scene* scene, const Collision& collision);

//----------------------------------------------------------------------------//
// --- Update Particle --- //
//----------------------------------------------------------------------------//

void updateVelocities(Scene* scene, unsigned int tIndex);
void updatePositions(Scene* scene, unsigned int tIndex);

#endif
