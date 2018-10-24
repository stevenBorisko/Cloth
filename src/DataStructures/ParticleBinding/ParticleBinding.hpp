#ifndef PARTICLE_H
#define PARTICLE_H

#include <cstring>
#include <vector>
#include <iterator>

#include "../../../lib/Matrix4/src/Matrix4.hpp"

#include "../../Displayable.hpp"

struct Binding;

struct Particle: Displayable {

	bool fixed;
	Vector4 position;
	Vector4 velocity;
	Vector4 force;
	float mass, radius, charge;
	std::vector<Binding*> bindings;

	// Constructors
	Particle();
	Particle(
		const bool& _dynamic,
		const Vector4& _position,
		const Vector4& _velocity,
		const float& _mass,
		const float& _radius
	);
	Particle(const Particle& other);
	// bindings should be deleted manually
	~Particle();

	// Operators
	Particle& operator=(const Particle& rhs);

	// Displayable Functions
	void setup();
	void update();
	//void draw(ofEasyCam& cam);

	// Miscellaneous
	void addBinding(Binding* binding);
	// Vector from buddy0 to buddy1
	Vector4 displacementTo(const Particle* particle) const;
	bool intersects(const Particle* particle) const;
	bool hasBuddy(const Particle* particle) const;

private:

	// Displayable data

};

struct Binding: Displayable {

	bool dynamic;
	float initDistance, errDistance;
	float springConstant;
	Particle* buddies[2];

	// Constructors
	Binding();
	// Implies static binding - not really tested yet
	Binding(
		Particle* thisParticle,
		Particle* otherParticle,
		const float& _springConstant
	);
	// Implies dynamic binding
	Binding(
		Particle* thisParticle,
		Particle* otherParticle,
		const float& _springConstant,
		const float& _initErrDistance
	);
	Binding(const Binding& other);
	~Binding();

	// Operators
	Binding& operator=(const Binding& rhs);

	// Displayable Functions
	void setup();
	void update();
	//void draw(ofEasyCam& cam);

	// Miscellaneous
	Vector4 getDisplacement() const;

private:
	// Displayable data
	//ofCylinderPrimitive shape;
	//ofMaterial shapeMaterial;

};

#endif
