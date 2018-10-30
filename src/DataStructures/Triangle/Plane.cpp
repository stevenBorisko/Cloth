#include "Triangle.hpp"

//----------------------------------------------------------------------------//
// --- Constructors --- //
//----------------------------------------------------------------------------//

Plane::Plane(): point(Vector4()), normal(Vector4()) { }

Plane::Plane(const Plane& other): point(other.point), normal(other.normal) { }

Plane::Plane(const Vector4& _point, const Vector4& _normal):
	point(_point), normal(_normal)
{ }

Plane::Plane(Particle* particles[3]):
	Plane(
		particles[0]->position,
		particles[1]->position,
		particles[2]->position
	)
{ }

Plane::Plane(const Vector4& p0, const Vector4& p1, const Vector4& p2):
	point(p0),
	normal(V_normalize(V_cross(p1 - p0, p2 - p0)))
{ }

Plane::~Plane() { }

//----------------------------------------------------------------------------//
// --- Operator Overloads --- //
//----------------------------------------------------------------------------//

Plane& Plane::operator=(const Plane& rhs) {
	this->point = rhs.point;
	this->normal = rhs.normal;
}

//----------------------------------------------------------------------------//
// --- Calculation --- //
//----------------------------------------------------------------------------//

double Plane::intersection(
	const Vector4& _point,
	const Vector4& _tangent
) const {
	double topDot = V_dot(this->normal, this->point - _point);
	double bottomDot = V_dot(this->normal, _tangent);
	return ((bottomDot == 0.0) || (bottomDot == -0.0))
		? DBL_MAX // tangent is parallel with plane
		: (topDot / bottomDot);
}
Vector4 Plane::projection(const Vector4& _point) const {
	double dist = this->intersection(_point, this->normal);
	return (this->normal * dist) + _point;
}
