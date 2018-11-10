#include "Physics.hpp"

#define COLLISION 50.0f

//----------------------------------------------------------------------------//
// --- Detection Implementation --- //
//----------------------------------------------------------------------------//

std::vector<Collision> collisionSphereSphere(Scene* scene, unsigned int tIndex){

	// variable delcaration
	Vector4 displacementVector, notMasses, forceAB;
	double displacement,intersection,sumOfRadii,massProd;

	unsigned int i, j;
	unsigned int pCount = scene->particles.size();
	bool APoint;

	Collision collision;
	std::vector<Collision> collisions;

	// iterate through each particle
	for (i = tIndex; i < pCount;i += THREAD_COUNT) {

		Particle* particleA = scene->particles[i];
		if(particleA->radius <= 0.0)
			continue;
		// iterate through each particle
		for (j = i+1; j < pCount;++j) {
			Particle* particleB = scene->particles[j];

			if(particleB->radius <= 0.0)
				continue;

			// no collisions between bound particles
			if (particleB->hasBuddy(particleA)) continue;

			displacementVector = particleA->displacementTo(particleB);
			displacement = V_magnitude(displacementVector);

			if(displacement == 0.0 || displacement == -0.0) continue;

			sumOfRadii = (particleA->radius + particleB->radius);
			intersection = sumOfRadii - displacement;

			// no collision
			if (intersection <= 0.0)
				continue;

			collision = {i,j,scene->triangles.size(),intersection};
			collisions.emplace_back(collision);

/*
			double coef = intersection;//std::log(intersection + 1.0);
			coef *= COLLISION * coef;
			// normalize if possible
			massProd = particleB->mass * particleA->mass;
			forceAB = displacementVector * (
				massProd
				* coef
				* (1 / (displacement * displacement))
			);

			particleB->addForce(forceAB);
			particleA->addForce(-forceAB);
*/
		}
	}
	return collisions;
}

std::vector<Collision> collisionSphereMesh(Scene* scene, unsigned int tIndex) {
	unsigned int i, j;
	unsigned int pCount = scene->particles.size();
	unsigned int tCount = scene->triangles.size();

	Particle* particle;
	Triangle* triangle;

	double intersection;
	Collision collision;
	std::vector<Collision> collisions;

	// iterate through each particle
	for (i = tIndex; i < pCount;i += THREAD_COUNT) {
		particle = scene->particles[i];
		if(particle->radius <= 0.0) continue;
		// iterate through each triangle
		for (j = 0; j < tCount;++j) {
			triangle = scene->triangles[j];

			// particle is a part of the triangle
			if(triangle->hasBuddy(particle)) continue;

			intersection = triangle->toCenterOf(particle);
			// TODO - Get future collision with triangle->intersection

			// no collision
			if(intersection >= particle->radius) continue;

			collision = {i,scene->particles.size(),j,intersection};
			collisions.emplace_back(collision);
		}
	}
	return collisions;
}

//----------------------------------------------------------------------------//
// --- Handling Implementation --- //
//----------------------------------------------------------------------------//

void collisionSphereSphere(Scene* scene, const Collision& collision) {
	
}

void collisionSphereMesh(Scene* scene, const Collision& collision) {

}
