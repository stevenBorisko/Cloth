#ifndef PHYSICS_H
#define PHYSICS_H

#include <pthread.h>

#define THREAD_COUNT 8

#include "../DataStructures/Scene/Scene.hpp"

//----------------------------------------------------------------------------//
// --- Struct Definitions --- //
//----------------------------------------------------------------------------//

/*
collider (long unsigned int)
	- Always the index of a particle
particle (long unsigned int)
	- if the collision was with a particle,
		this is the index of that particle;
	- else
		the size of the particle list.
triangle (long unsigned int)
	- if the collision was with a mesh,
		this is the index of the triangle within that mesh;
	- else
		the size of the triangle list.
intersection (double):
	(0.0, 1.0]: The collision is in the future.
		This is how far into the time step it occurs.
	(0.0, RS): The collision is happening right now.
		This is the distance from the edge of `collider` to the edge of the
			colliding geometry. If the colliding geometry is another sphere,
			then this is the distance to the edge of the sphere. If is mesh,
			it is the distance to the triangle's plane.
		Essentially, it is the amount the geometry is overlapping.
		RS is radius sum. If the overlapping geometry is another sphere, there
			is no way the intersection will be more than the sum of the radii
future (bool)
	true: the collision will happen within the time step
	false: the collision is happening now
		(the geometry is currently overlapping)
	If `collider` is sizeless, this will always be true

Documentation of a collision. The purpose is to be able to handle collisions
	at a different time than when they are detected.
The three indices (`collider`, `particle`, and `triangle`) are the indices
	within some scene.
*/
struct Collision {
	long unsigned int collider, particle, triangle;
	double intersection;
	bool future;
};

//----------------------------------------------------------------------------//
// --- Threads --- //
//----------------------------------------------------------------------------//

/*
scene (Scene*)
	- The scene being analyzed
index (unsigned int)
	- The index of the thread
collisions (std::vector<Collision>)
	- All the collisions detected within the scene so far
*/
struct ThreadData {
	Scene* scene;
	unsigned int index;
	std::vector<Collision> collisions;
};

void t_execute(void* (*t_func)(void*), ThreadData tds[THREAD_COUNT]);

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
