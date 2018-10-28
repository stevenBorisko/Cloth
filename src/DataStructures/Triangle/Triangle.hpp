#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../../../lib/Matrix4/src/Matrix4.hpp"

#include "../ParticleBinding/ParticleBinding.hpp"

struct Plane;

struct Triangle {

	Binding* bindings[3];

	Triangle();
	Triangle(const Triangle& other);
	~Triangle();

	Triangle& operator=(const Triangle& rhs);

	void update();
	void draw();

};

struct Plane {
	Vector4 point;
	Vector4 normal;
};

#endif
