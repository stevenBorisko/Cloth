#include "Triangle.hpp"

Triangle& Triangle::operator=(const Triangle& rhs) {
	this->particles[0] = rhs.particles[0];
	this->particles[1] = rhs.particles[1];
	this->particles[2] = rhs.particles[2];
	return *this;
}
