#include "Physics.hpp"
#include "../DataStructures/Scene/Scene.hpp"

void PhysicsEngine::updateScene(Scene* scene) {

	// reset the particles' forces
	for(auto& particle : scene->particles)
		particle->force = Vector4();

	// forces
	forceGravity(scene);
	forceBinding(scene);

	// collisions
	collisionParticleParticle(scene);

	// update particles
	updateVelocities(scene);
	updatePositions(scene);
	return;
}
