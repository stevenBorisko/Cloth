#include "ParticleBinding.hpp"

//----------------------------------------------------------------------------//
// Constructors //
//----------------------------------------------------------------------------//

Particle::Particle():
	fixed(false),
	position(Vector4()),
	velocity(Vector4()),
	force(Vector4()),
	mass(0.0),
	radius(10),
	charge(0.0),
	bindings(std::vector<Binding*>())
{ }

Particle::Particle(
	const bool& _dynamic,
	const Vector4& _position,
	const Vector4& _velocity,
	const float& _mass,
	const float& _radius
):
	fixed(!_dynamic),
	position(_position),
	velocity(_velocity),
	force(Vector4()),
	mass(_mass),
	radius(_radius),
	charge(0.0),
	bindings(std::vector<Binding*>())
{ }

Particle::Particle(const Particle& other):
	fixed(other.fixed),
	position(other.position),
	velocity(other.velocity),
	force(other.force),
	mass(other.mass),
	radius(other.radius),
	charge(other.charge),
	bindings(other.bindings)
{ }

Particle::~Particle() { }

//----------------------------------------------------------------------------//
// Operators //
//----------------------------------------------------------------------------//

Particle& Particle::operator=(const Particle& rhs) {

	this->fixed = rhs.fixed;
	this->position = rhs.position;
	this->velocity = rhs.velocity;
	this->force = rhs.force;
	this->mass = rhs.mass;
	this->radius = rhs.radius;
	this->charge = rhs.charge;
	this->bindings = rhs.bindings;

	return *this;
}

//----------------------------------------------------------------------------//
// Displayable Functions //
//----------------------------------------------------------------------------//

void Particle::setup() {
/*
	this->shape.setRadius(this->radius);
	this->shape.setPosition(
		ofVec3f(
			this->position.x,
			this->position.y,
			this->position.z
		)
	);

	this->shapeMaterial.setDiffuseColor(ofFloatColor(0.1, 0.9, 0.1));
	this->shapeMaterial.setSpecularColor(ofFloatColor(0.1, 0.1, 0.1));
	this->shapeMaterial.setShininess(2.0);
*/
}

void Particle::update() {
/*
	this->shape.setPosition(
		ofVec3f(
			this->position.x,
			this->position.y,
			this->position.z
		)
	);
	//this->shape.setRadius(this->radius);
*/
}

/*
void Particle::draw(ofEasyCam& cam) {
	cam.begin();
	this->shapeMaterial.begin();
	this->shape.draw();
	this->shapeMaterial.end();
	cam.end();
}
*/

//----------------------------------------------------------------------------//
// Miscellaneous //
//----------------------------------------------------------------------------//

void Particle::addBinding(Binding* binding) {
	this->bindings.emplace_back(binding);
}

Vector4 Particle::displacementTo(const Particle* particle) const {
	return particle->position - this->position;
}

bool Particle::intersects(const Particle* particle) const {
	return V_magnitude(this->displacementTo(particle)) <= (this->radius + particle->radius);
}

bool Particle::hasBuddy(const Particle* particle) const {
	for (auto& binding : this->bindings)
		if(binding->buddies[0] == particle || binding->buddies[0] == particle)
			return true;
	return false;
}
