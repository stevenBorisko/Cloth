#include "Triangle.hpp"

Triangle::Triangle() {
	this->bindings[0] = nullptr;
	this->bindings[1] = nullptr;
	this->bindings[2] = nullptr;
}

Triangle::Triangle(const Triangle& other) {
	this->bindings[0] = other.bindings[0];
	this->bindings[1] = other.bindings[1];
	this->bindings[2] = other.bindings[2];
}

Triangle::~Triangle() { }
