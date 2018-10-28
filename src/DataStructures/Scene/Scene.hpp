#ifndef SCENE_H
#define SCENE_H

#include "../Triangle/Triangle.hpp"
#include "../ParticleBinding/ParticleBinding.hpp"

#define TICKS_PER_SECOND 600
#define TIME_STEP ((double)1.0 / (double)TICKS_PER_SECOND)

struct Scene {

	// Public Data
	std::vector<Particle*> particles;
	std::vector<Binding*> bindings;
	std::vector<Triangle*> triangles;
	double globalGravity;
	unsigned long long tick;

	// Constructors
	Scene();
	Scene(const Scene& other);
	Scene(
		std::vector<Particle*> _particles,
		std::vector<Binding*> _bindings,
		std::vector<Triangle*> _triangles,
		const double& _globalGravity
	);
	// Particles and bindings should be deleted manually
	~Scene();

	// Operators
	Scene& operator=(const Scene& rhs);

	// Displayable Functions
	void setup();
	void update(Scene* swap);
	void draw();

	// Miscellaneous
	void addParticle(Particle* particle);
	void addBinding(Binding* binding);
	void addTriangle(Triangle* triangle);
	void addParticles(std::vector<Particle*> _particles);
	void addBindings(std::vector<Binding*> _bindings);
	void addTriangles(std::vector<Triangle*> _triangles);

	// Copying
	void deepCopyFrom(const Scene* other);
	void deepCopyInto(Scene* other) const;
};

struct PhysicsEngine {
	static void updateScene(Scene* scene, Scene* swap);
};


#endif
