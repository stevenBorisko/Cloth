#ifndef PHYSICS_H
#define PHYSICS_H

#include <pthread.h>

#define THREAD_COUNT 8

#include "../DataStructures/Scene/Scene.hpp"

//----------------------------------------------------------------------------//
// --- Struct Definitions --- //
//----------------------------------------------------------------------------//

/*
--- struct Collision ---

collider (long unsigned int)
	- Always the index of a particle

particle (long unsigned int)
	the collision was with a particle:
		this is the index of that particle
	else: the size of the particle list

triangle (long unsigned int)
	the collision was with a mesh:
		this is the index of the triangle within that mesh
	else: the size of the triangle list

intersection (double):
	(0.0, 1.0]: The collision is in the future.
		This is how far into the time step it occurs.
	(0.0, RS): The collision is happening right now.
		This is the distance from the edge of `collider` to the edge of the
			colliding geometry. If the colliding geometry is another sphere,
			then this is the distance to the edge of the sphere. If is mesh,
			it is the distance to the triangle's plane.
		Essentially, it is the amount the geometry is overlapping.
		RS is radius sum. If the overlapping geometry is another sphere,
			an intersection greater than the sum of the radii is impossible

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
--- struct ThreadData ---

scene (Scene*)
	- The scene being analyzed
index (unsigned int)
	- The index of the thread
collisions (std::vector<Collision>)
	- All the collisions detected within the scene so far

Data structure to be sent to a POSIX thread function
*/
struct ThreadData {
	Scene* scene;
	unsigned int index;
	std::vector<Collision> collisions;
};

/*
--- void t_execute(void* (*)(void*), ThreadData[THREAD_COUNT]) ---
Implementation file: PhysicsEngine.cpp

t_func (void* (*)(void*)
	- POSIX thread compliant function
	- The argument that it expects must be a ThreadData struct
	- Each function will get one of the structs in `tds`
tds (ThreadData[THREAD_COUNT])
	- Data to be sent along with each thread
Creates and joins `THREAD_COUNT` threads each calling a POSIX thread compliant
	function with its own data structure
*/
void t_execute(void* (*t_func)(void*), ThreadData tds[THREAD_COUNT]);

//----------------------------------------------------------------------------//
// --- Forces --- //
//----------------------------------------------------------------------------//

/*
--- void force*(Scene*, unsigned int) ---
Implementation file: Forces.cpp

scene (Scene*)
	- Scene being analyzed
tIndex (unsigned int)
	- index of the thread executing this function

Calculate a specific force on all the particles in the scene.
*/
// Force of gravity specified in `scene` as `globalGravity`
void forceGravity(Scene* scene, unsigned int tIndex);
// Force of the spring binding between each particle
void forceBinding(Scene* scene, unsigned int tIndex);

//----------------------------------------------------------------------------//
// --- Collision Detection --- //
//----------------------------------------------------------------------------//

/*
--- std::vector<Collision> collision*(Scene* unsigned int) ---
Implementation file: Collisions/Detection.cpp

scene (Scene*)
	- Scene being analyzed
tIndex (unsigned int)
	- index of the thread executing this function

return (std::vector<Collision>)
	- The collisions detected by this thread
	- Will be appended to another vector of collisions

Detect a specific collision type. Returns a vector of all the documented
	collisions
*/
// (Particles of radius > 0.0) and (particles of radius > 0.0)
std::vector<Collision> collisionSphereSphere(Scene* scene, unsigned int tIndex);
// (Particles of radius > 0.0) and (triangulated mesh)
std::vector<Collision> collisionSphereMesh(Scene* scene, unsigned int tIndex);

//----------------------------------------------------------------------------//
// --- Collision Handling --- //
//----------------------------------------------------------------------------//

/*
--- *estFutureCollision(std::vector<Collision>&) ---
Implementation file: Collisions/Handling.cpp

collisions (std::vector<Collision>&)
	- All collisions detected

return (double)
	(0.0, 1.0): The intersection point within the time step.
	else: All collisions are current
*/
double nearestFutureCollision(std::vector<Collision>& collisions);
double farthestFutureCollision(std::vector<Collision>& collisions);

/*
--- void collision*(Scene*, const Collision&) ---
Implementation file: Collisions/Handling.cpp

scene (Scene*)
	- The scene being analyzed
collision (const Collision&)
	- the collision being handled

These functions will change the velocity and zero the forces on the affected
	particles, so the Update Particle functions don't need to check for these
	special cases.
*/
void collisionSphereSphere(Scene* scene, const Collision& collision);
void collisionSphereMesh(Scene* scene, const Collision& collision);

//----------------------------------------------------------------------------//
// --- Update Particle --- //
//----------------------------------------------------------------------------//

/*
--- void update*(Scene* unsigned int tIndex) ---
Implementation file: UpdateParticle.cpp

scene (Scene*)
	- Scene to be updated
tIndex (unsigned int)
	- index of the thread executing this function
*/
// Change velocities based on forces
void updateVelocities(Scene* scene, unsigned int tIndex);
// Change positions based on velocities
void updatePositions(Scene* scene, unsigned int tIndex);

#endif
