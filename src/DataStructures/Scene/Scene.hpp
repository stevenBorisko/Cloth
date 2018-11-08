#ifndef SCENE_H
#define SCENE_H

#include "../Triangle/Triangle.hpp"
#include "../ParticleBinding/ParticleBinding.hpp"

#define TICKS_PER_SECOND 1200
#define TIME_STEP ((double)1.0 / (double)TICKS_PER_SECOND)

// Visibility Macros
#define PARTICLES_VISIBLE (1<<0)
#define PARTICLES_SIZE_VISIBLE (1<<1)
#define BINDINGS_VISIBLE (1<<2)
#define TRIANGLES_VISIBLE (1<<3)

struct Scene;

struct SceneSwap {
	std::vector<ParticleSmall> particles;

	SceneSwap();
	SceneSwap(const SceneSwap& other);
	SceneSwap(const Scene& scene);
	~SceneSwap();

	SceneSwap& operator=(const SceneSwap& rhs);
	SceneSwap& operator=(const Scene& rhs);
};

struct Scene {

	// Public Data
	std::vector<Particle*> particles;
	std::vector<Binding*> bindings;
	std::vector<Triangle*> triangles;
	double globalGravity;
	char visibility;
	unsigned long long tick;

	SceneSwap swap;

	// Constructors
	Scene();
	Scene(const Scene& other);
	Scene(
		std::vector<Particle*> _particles,
		std::vector<Binding*> _bindings,
		std::vector<Triangle*> _triangles,
		const double& _globalGravity,
		const char& _visibility
	);
	// Particles and bindings should be deleted manually
	~Scene();

	// Operators
	Scene& operator=(const Scene& rhs);

	// Displayable Functions
	void update();
	// backs up all particle positions to `swap`
	void backup();
	// reverts to the data in `swap`
	void reset();
	void draw();
	void setVisibility(char _visibility);

	// Append
	void addParticle(Particle* particle);
	void addBinding(Binding* binding);
	void addTriangle(Triangle* triangle);
	void addParticles(std::vector<Particle*> _particles);
	void addBindings(std::vector<Binding*> _bindings);
	void addTriangles(std::vector<Triangle*> _triangles);
};

struct PhysicsEngine {
	static void updateScene(Scene* scene);
};


#endif
