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
/*
void Binding::draw(ofEasyCam& cam) {
}
	ofVec4f _start, _end;
	ofVec3f start, end;

	_start = this->buddies[0]->position;
	_end = this->buddies[1]->position;

	ofDrawLine(_start.x, _start.y, _start.z, _end.x, _end.y, _end.z);

}*/

//----------------------------------------------------------------------------//
// Miscellaneous Functions //
//----------------------------------------------------------------------------//

Vector4 Binding::getDisplacement() const {
	return this->buddies[0]->displacementTo(this->buddies[1]);
}
