#include "Triangle.hpp"

Triangle& Triangle::operator=(const Triangle& rhs) {
	this->bindings[0] = rhs.bindings[0];
	this->bindings[1] = rhs.bindings[1];
	this->bindings[2] = rhs.bindings[2];
	return *this;
}
