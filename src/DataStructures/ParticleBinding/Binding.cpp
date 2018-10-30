#include "ParticleBinding.hpp"

//----------------------------------------------------------------------------//
// Constructors //
//----------------------------------------------------------------------------//

Binding::Binding():
	dynamic(false),
	restDistance(0),
	errDistance(0),
	springConstant(0),
	lock(nullptr)
{
	buddies[0] = nullptr;
	buddies[1] = nullptr;
}

Binding::Binding(
	Particle* particleA,
	Particle* particleB,
	const double& _springConstant
):
	Binding(particleA,particleB,_springConstant,0.0)
{
	dynamic = false;
}

Binding::Binding(
	Particle* particleA,
	Particle* particleB,
	const double& _springConstant,
	const double& _initErrDistance
):
	dynamic(true),
	restDistance(
		V_magnitude(particleA->position - particleB->position)
		- _initErrDistance
	),
	springConstant(_springConstant),
	errDistance(_initErrDistance),
	lock(new pthread_mutex_t)
{
	this->buddies[0] = particleA;
	this->buddies[1] = particleB;
	particleA->addBinding(this);
	particleB->addBinding(this);

	pthread_mutex_init(this->lock,nullptr);
}

Binding::Binding(const Binding& other):
	dynamic(other.dynamic),
	restDistance(other.restDistance),
	errDistance(other.errDistance),
	springConstant(other.springConstant),
	lock(other.lock)
{
	this->buddies[0] = other.buddies[0];
	this->buddies[1] = other.buddies[1];
}

Binding::~Binding() {
	if(this->lock) {
		pthread_mutex_destroy(this->lock);
		delete this->lock;
	}
}

//----------------------------------------------------------------------------//
// Operators //
//----------------------------------------------------------------------------//

Binding& Binding::operator=(const Binding& rhs) {
	this->dynamic = rhs.dynamic;
	this->restDistance = rhs.restDistance;
	this->errDistance = rhs.errDistance;
	this->springConstant = rhs.springConstant;
	this->buddies[0] = rhs.buddies[0];
	this->buddies[1] = rhs.buddies[1];

	this->lock = rhs.lock;

	return *this;
}

//----------------------------------------------------------------------------//
// Displayable Functions //
//----------------------------------------------------------------------------//

void Binding::update() { }
void Binding::draw() {
	Vector4 buddyPositions[2] = {
		this->buddies[0]->position,
		this->buddies[1]->position
	};
	ColorRGB color = this->getColor();

	glBegin(GL_LINES);
	glColor3f(color.r,color.g,color.b);
	glVertex3f(buddyPositions[0][0],buddyPositions[0][1],buddyPositions[0][2]);
	glVertex3f(buddyPositions[1][0],buddyPositions[1][1],buddyPositions[1][2]);
	glEnd();

}

//----------------------------------------------------------------------------//
// Setters //
//----------------------------------------------------------------------------//

void Binding::addDistance(const double& distance) {
	pthread_mutex_lock(this->lock);
	this->restDistance += distance;
	pthread_mutex_unlock(this->lock);
}

void Binding::makeFirst(Particle* particle) {
	if(this->buddies[0] != particle) {
		this->buddies[1] = this->buddies[0];
		this->buddies[0] = particle;
	}
}

//----------------------------------------------------------------------------//
// Getters //
//----------------------------------------------------------------------------//

Vector4 Binding::getDisplacement() const {
	return this->buddies[0]->displacementTo(this->buddies[1]);
}

bool Binding::hasBuddy(const Particle* particle) const {
	return ((this->buddies[0] == particle) | (this->buddies[1] == particle));
}

Particle* Binding::getOtherBuddy(const Particle* particle) const {
	return this->buddies[this->buddies[0] == particle];
}

ColorRGB Binding::getColor() const {
	double err = 2.0 * this->errDistance / this->restDistance;
	return (err > 0.0)
		? ColorRGB(
			std::min(1.0,err),
			std::max(0.0,0.5-err),
			std::max(0.0,1.0-err)
		)
		: ColorRGB(0.0,0.5,1.0);
}
