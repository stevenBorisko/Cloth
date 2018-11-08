#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cmath>
#include <float.h>

#include "../../../lib/Matrix4/src/Matrix4.hpp"

#include "../ParticleBinding/ParticleBinding.hpp"
#include "../../Graphics/Color/Color.hpp"

struct Plane;

struct Triangle {

	Particle* particles[3];
	Binding* bindings[3];
	Plane* plane;

	// Constructors
	Triangle();
	Triangle(const Triangle& other);
	Triangle(Particle* _particles[3]);
	Triangle(Particle* p0, Particle* p1, Particle* p2);
	~Triangle();

	// Operator Overloads
	Triangle& operator=(const Triangle& rhs);

	// Displayables
	void update();
	void draw();

	// Calculation
	// assumes point is on the plane of the triangle
	// calls `orient`
	bool containsPoint(const Vector4& point);
	double intersection(const Vector4& position, const Vector4& velocity) const;
	double toCenterOf(const Particle* particle) const;

	// Getters
	bool hasBuddy(const Particle* particle) const;
	double getMass() const;

private:
	void orient();
};

struct Plane {
	Vector4 point;
	Vector4 normal;

	// Constructors
	Plane();
	Plane(const Plane& other);
	Plane(const Vector4& _point, const Vector4& _normal);
	Plane(Particle* particles[3]);
	Plane(const Vector4& p0, const Vector4& p1, const Vector4& p2);
	~Plane();

	// Operator Overloads
	Plane& operator=(const Plane& rhs);

	// Calculation
	// gives the distance along the vector `_tangent`
	// starting at point `_point`
	double intersection(
		const Vector4& _point,
		const Vector4& _tangent
	) const;
	Vector4 projection(const Vector4& _point) const;
};

#endif
