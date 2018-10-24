#ifndef PHYSICS_H
#define PHYSICS_H

#define TIME_STEP (1.0f / 180.0f)

#include "../DataStructures/Scene/Scene.hpp"

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
