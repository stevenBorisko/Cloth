#include "Triangle.hpp"

//----------------------------------------------------------------------------//
// --- Constructors --- //
//----------------------------------------------------------------------------//

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

//----------------------------------------------------------------------------//
// --- Operator Overloads --- //
//----------------------------------------------------------------------------//

Triangle& Triangle::operator=(const Triangle& rhs) {
	this->particles[0] = rhs.particles[0];
	this->particles[1] = rhs.particles[1];
	this->particles[2] = rhs.particles[2];
	return *this;
}

//----------------------------------------------------------------------------//
// --- Displayables --- //
//----------------------------------------------------------------------------//

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

//----------------------------------------------------------------------------//
// --- Calculation --- //
//----------------------------------------------------------------------------//

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

//----------------------------------------------------------------------------//
// --- Getters --- //
//----------------------------------------------------------------------------//

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

//----------------------------------------------------------------------------//
// --- Private --- //
//----------------------------------------------------------------------------//

void Triangle::orient() {
	this->bindings[0]->makeFirst(this->particles[0]);
	this->bindings[1]->makeFirst(this->particles[1]);
	this->bindings[2]->makeFirst(this->particles[2]);
}
