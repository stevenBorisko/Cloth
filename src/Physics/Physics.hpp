#ifndef PHYSICS_H
#define PHYSICS_H

#include <pthread.h>

#define TIME_STEP (1.0f / 512.0f)
#define THREAD_COUNT 4

#include "../DataStructures/Scene/Scene.hpp"

struct ThreadData {
	Scene* scene;
	unsigned int index;
};

//----------------------------------------------------------------------------//
// Forces //
//----------------------------------------------------------------------------//

void forceGravity(Scene* scene);
void forceBinding(Scene* scene);

//----------------------------------------------------------------------------//
// Collision //
//----------------------------------------------------------------------------//

void collisionParticleParticle(Scene* scene);

//----------------------------------------------------------------------------//
// Update Particle //
//----------------------------------------------------------------------------//

void updateVelocities(Scene* scene);
void updatePositions(Scene* scene);

#endif
