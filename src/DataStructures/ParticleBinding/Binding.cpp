#include "ParticleBinding.hpp"

//----------------------------------------------------------------------------//
// Constructors //
//----------------------------------------------------------------------------//

Binding::Binding():
	dynamic(false),
	initDistance(0),
	errDistance(0),
	springConstant(0)
{
	buddies[0] = nullptr;
	buddies[1] = nullptr;
}

Binding::Binding(
	Particle* particleA,
	Particle* particleB,
	const float& _springConstant
):
	Binding(particleA,particleB,_springConstant,0.0)
{
	dynamic = false;
}

Binding::Binding(
	Particle* particleA,
	Particle* particleB,
	const float& _springConstant,
	const float& _initErrDistance
):
	dynamic(true),
	initDistance(
		V_magnitude(particleA->position - particleB->position)
		- _initErrDistance
	),
	springConstant(_springConstant),
	errDistance(_initErrDistance)
{
	this->buddies[0] = particleA;
	this->buddies[1] = particleB;
	particleA->addBinding(this);
	particleB->addBinding(this);
}

Binding::Binding(const Binding& other):
	dynamic(other.dynamic),
	initDistance(other.initDistance),
	errDistance(other.errDistance),
	springConstant(other.springConstant)
{
	this->buddies[0] = other.buddies[0];
	this->buddies[1] = other.buddies[1];
}

Binding::~Binding() { }

//----------------------------------------------------------------------------//
// Operators //
//----------------------------------------------------------------------------//

Binding& Binding::operator=(const Binding& rhs) {
	this->dynamic = rhs.dynamic;
	this->initDistance = rhs.initDistance;
	this->errDistance = rhs.errDistance;
	this->springConstant = rhs.springConstant;
	this->buddies[0] = rhs.buddies[0];
	this->buddies[1] = rhs.buddies[1];
	return *this;
}

//----------------------------------------------------------------------------//
// Displayable Functions //
//----------------------------------------------------------------------------//

void Binding::setup() { }
void Binding::update() { }
void Binding::draw() {
	Vector4 buddyPositions[2] = {
		this->buddies[0]->position,
		this->buddies[1]->position
	};
	glBegin(GL_LINES);
	glColor3f(1,1,1);
	if(this->errDistance != 0.0 && this->errDistance != -0.0) {
		float ratio = this->errDistance / this->initDistance;
		float others = std::max(0.0, 1.0 - (ratio * 4.0));
		if(ratio > 0.0)
			glColor3f(1.0,others,others);
	}
	glVertex3f(buddyPositions[0][0],buddyPositions[0][1],buddyPositions[0][2]);
	glVertex3f(buddyPositions[1][0],buddyPositions[1][1],buddyPositions[1][2]);
	glEnd();
}

//----------------------------------------------------------------------------//
// Miscellaneous Functions //
//----------------------------------------------------------------------------//

Vector4 Binding::getDisplacement() const {
	return this->buddies[0]->displacementTo(this->buddies[1]);
}
