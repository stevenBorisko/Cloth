#include "Triangle.hpp"

void Triangle::update() {
	*this->plane = Plane(this->particles);
}

void Triangle::draw() {
	const ColorRGB colors[3] = {
		this->particles[0]->getColor(),
		this->particles[1]->getColor(),
		this->particles[2]->getColor()
	};
	// TODO: gradient somehow
}
