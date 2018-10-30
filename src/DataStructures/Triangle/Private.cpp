#include "Triangle.hpp"

void Triangle::orient() {
	this->bindings[0]->makeFirst(this->particles[0]);
	this->bindings[1]->makeFirst(this->particles[1]);
	this->bindings[2]->makeFirst(this->particles[2]);
}
