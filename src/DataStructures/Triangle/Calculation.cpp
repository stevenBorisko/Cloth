#include "Triangle.hpp"

bool Triangle::containsPoint(const Vector4& point) {
	Vector4 crosses[3];
	double dots[2];

	this->orient();

	// Get cross products
	crosses[0] = V_cross(
		this->bindings[0]->getDisplacement(),
		point - this->particles[0]->position
	);
	crosses[1] = V_cross(
		this->bindings[1]->getDisplacement(),
		point - this->particles[1]->position
	);
	crosses[2] = V_cross(
		this->bindings[2]->getDisplacement(),
		point - this->particles[2]->position
	);

	// Get dot products
	dots[0] = V_dot(crosses[0],crosses[1]);
	dots[1] = V_dot(crosses[1],crosses[2]);

	return ((dots[0] > 0.0) & (dots[1] > 0.0));
}

double Triangle::intersection(const Particle* particle) const {
	return std::abs(
		this->plane->intersection(
			particle->position,
			this->plane->normal
		)
	);
}
