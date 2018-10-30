#include "Triangle.hpp"

Triangle::Triangle(): plane(nullptr) {
	this->particles[0] = nullptr;
	this->particles[1] = nullptr;
	this->particles[2] = nullptr;

	this->bindings[0] = nullptr;
	this->bindings[1] = nullptr;
	this->bindings[2] = nullptr;
}

Triangle::Triangle(const Triangle& other):
	plane(new Plane(*other.plane))
{
	this->particles[0] = other.particles[0];
	this->particles[1] = other.particles[1];
	this->particles[2] = other.particles[2];

	this->bindings[0] = other.bindings[0];
	this->bindings[1] = other.bindings[1];
	this->bindings[2] = other.bindings[2];
}

Triangle::Triangle(Particle* _particles[3]):
	Triangle(_particles[0],_particles[1],_particles[2])
{ }

Triangle::Triangle(Particle* p0, Particle* p1, Particle* p2) {
	this->particles[0] = p0;
	this->particles[1] = p1;
	this->particles[2] = p2;

	this->bindings[0] = this->particles[0]->getBindingTo(this->particles[1]);
	this->bindings[1] = this->particles[1]->getBindingTo(this->particles[2]);
	this->bindings[2] = this->particles[2]->getBindingTo(this->particles[0]);

	this->plane = new Plane(this->particles);
}

Triangle::~Triangle() {
	if(this->plane) delete this->plane;
}
