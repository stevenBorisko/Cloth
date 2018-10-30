#include "Triangle.hpp"

bool Triangle::hasBuddy(const Particle* particle) const {
	return (particles[0] == particle)
		|| (particles[1] == particle)
		|| (particles[2] == particle);
}

double Triangle::getMass() const {
	return this->particles[0]->mass
		+ this->particles[1]->mass
		+ this->particles[2]->mass;
}
