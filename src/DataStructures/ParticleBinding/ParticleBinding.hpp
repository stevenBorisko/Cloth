#ifndef PARTICLE_H
#define PARTICLE_H

#ifdef __APPLE__
#include <GLUT/gl.h>
#include <GLUT/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

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
	double mass, radius, charge;
	std::vector<Binding*> bindings;

	// Constructors
	Particle();
	Particle(
		const bool& _dynamic,
		const Vector4& _position,
		const Vector4& _velocity,
		const double& _mass,
		const double& _radius
	);
	Particle(const Particle& other);
	// bindings should be deleted manually
	~Particle();

	// Operators
	Particle& operator=(const Particle& rhs);

	// Displayable Functions
	void setup();
	void update();
	void draw();

	// Setters
	void addBinding(Binding* binding);
	void addForce(const Vector4& _force);

	// Getters
	// Vector from buddy0 to buddy1
	Vector4 displacementTo(const Particle* particle) const;
	bool intersects(const Particle* particle) const;
	bool hasBuddy(const Particle* particle) const;

private:

	pthread_mutex_t* lock;

};

struct Binding: Displayable {

	bool dynamic;
	double restDistance, errDistance;
	double springConstant;
	Particle* buddies[2];

	// Constructors
	Binding();
	// Implies static binding - not really tested yet
	Binding(
		Particle* thisParticle,
		Particle* otherParticle,
		const double& _springConstant
	);
	// Implies dynamic binding
	Binding(
		Particle* thisParticle,
		Particle* otherParticle,
		const double& _springConstant,
		const double& _initErrDistance
	);
	Binding(const Binding& other);
	~Binding();

	// Operators
	Binding& operator=(const Binding& rhs);

	// Displayable Functions
	void setup();
	void update();
	void draw();

	// Setters
	void addDistance(const double& distance);

	// Getters
	Vector4 getDisplacement() const;

private:

	pthread_mutex_t* lock;

};

#endif
