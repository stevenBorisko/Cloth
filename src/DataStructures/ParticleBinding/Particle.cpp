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
	bindings(std::vector<Binding*>()),
	lock(nullptr)
{ }

Particle::Particle(
	const bool& _dynamic,
	const Vector4& _position,
	const Vector4& _velocity,
	const double& _mass,
	const double& _radius
):
	fixed(!_dynamic),
	position(_position),
	velocity(_velocity),
	force(Vector4()),
	mass(_mass),
	radius(_radius),
	charge(0.0),
	bindings(std::vector<Binding*>()),
	lock(new pthread_mutex_t)
{
	pthread_mutex_init(lock, nullptr);
}

Particle::Particle(const Particle& other):
	fixed(other.fixed),
	position(other.position),
	velocity(other.velocity),
	force(other.force),
	mass(other.mass),
	radius(other.radius),
	charge(other.charge),
	bindings(other.bindings),
	lock(other.lock)
{ }

Particle::~Particle() {
	if(this->lock) {
		pthread_mutex_destroy(lock);
		delete(lock);
	}
}

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

	this->lock = rhs.lock;

	return *this;
}

//----------------------------------------------------------------------------//
// Displayable Functions //
//----------------------------------------------------------------------------//

void Particle::update() { }
void Particle::draw() {
	ColorRGB color = this->getColor();
	// particle is a sphere
	if(this->radius > 0.0) {
		glColor3f(color.r,color.g,color.b);
		glPushMatrix();
		glTranslatef(this->position[0],this->position[1],this->position[2]);
		glutWireSphere(this->radius,10,10);
		glPopMatrix();
	// particle is a point
	} else {
		glBegin(GL_POINTS);
		glColor3f(color.r,color.g,color.b);
		glVertex3f(this->position[0],this->position[1],this->position[2]);
		glEnd();
	}
}

//----------------------------------------------------------------------------//
// Setters //
//----------------------------------------------------------------------------//
// These will typically need to use a lock

void Particle::addBinding(Binding* binding) {
	this->bindings.emplace_back(binding);
}

void Particle::addForce(const Vector4& _force) {
	pthread_mutex_lock(this->lock);
	this->force += _force;
	pthread_mutex_unlock(this->lock);
}

//----------------------------------------------------------------------------//
// Getters //
//----------------------------------------------------------------------------//

Vector4 Particle::displacementTo(const Particle* particle) const {
	return particle->position - this->position;
}

bool Particle::intersects(const Particle* particle) const {
	return V_magnitude(this->displacementTo(particle)) <= (this->radius + particle->radius);
}

bool Particle::hasBuddy(const Particle* particle) const {
	return !!this->getBindingTo(particle);
}

Binding* Particle::getBindingTo(const Particle* particle) const {
	for (auto& binding : this->bindings)
		if(binding->hasBuddy(particle))
			return binding;
	return nullptr;
}

ColorRGB Particle::getColor() const {
	double div, err = 0.0;

	if(!this->bindings.size())
		return ColorRGB(0.8,0.8,0.8);

	for(auto& binding : this->bindings) {
		div = binding->errDistance / binding->restDistance;
		if(div >= 0.0) err += div;
	}
	err *= 2.0;

	return (err > 0.0)
		? ColorRGB(
			std::min(1.0,err),
			std::max(0.0,0.5-err),
			std::max(0.0,1.0-err)
		)
		: ColorRGB(0.0,0.5,1.0);
}
