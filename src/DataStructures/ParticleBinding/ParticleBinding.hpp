#ifndef PARTICLE_H
#define PARTICLE_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <cstring>
#include <vector>
#include <iterator>

#include "../../../lib/Matrix4/src/Matrix4.hpp"
#include "../../Graphics/Color/Color.hpp"

struct Binding;

struct Particle {

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

	// Operator Overloads
	Particle& operator=(const Particle& rhs);

	// Displayable Functions
	void update();
	void draw();

	// Setters
	void addBinding(Binding* binding);
	void addForce(const Vector4& _force);

	// Getters
	// Vector from buddy0 to buddy1
	Vector4 displacementTo(const Particle* particle) const;
	bool intersects(const Particle* particle) const;
	// if one of the bindings has `particle` as a buddy
	bool hasBuddy(const Particle* particle) const;
	// retrieves the binding that has `this` and `particle` as buddies
	// nullptr if there is no binding to `particle`
	Binding* getBindingTo(const Particle* particle) const;
	ColorRGB getColor() const;

private:

	pthread_mutex_t* lock;

};

struct Binding {

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
	void update();
	void draw();

	// Setters
	void addDistance(const double& distance);
	// makes `particle` buddy[0] (flips them if necessary)
	void makeFirst(Particle* particle);

	// Getters
	Vector4 getDisplacement() const;
	bool hasBuddy(const Particle* particle) const;
	Particle* getOtherBuddy(const Particle* particle) const;
	ColorRGB getColor() const;

private:

	pthread_mutex_t* lock;

};

#endif
