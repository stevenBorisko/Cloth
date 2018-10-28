#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../ParticleBinding/ParticleBinding.hpp"

struct Triangle {

	Binding* bindings[3];

	Triangle();
	Triangle(const Triangle& other);
	~Triangle();

	Triangle& operator=(const Triangle& rhs);

	void update();
	void draw();

};

#endif
