#ifndef SCENE_H
#define SCENE_H

#include "../ParticleBinding/ParticleBinding.hpp"

struct Scene: Displayable {
	//TODO: start using std::vector<>

	// Public Data
	std::vector<Particle*> particles;
	std::vector<Binding*> bindings;
	float globalGravity;
	unsigned long long tick;

	// Constructors
	Scene();
	Scene(const Scene& other);
	Scene(
		std::vector<Particle*> _particles,
		std::vector<Binding*> _bindings,
		const float& _globalGravity
	);
	// Particles and bindings should be deleted manually
	~Scene();

	// Operators
	Scene& operator=(const Scene& rhs);

	// Displayable Functions
	void setup();
	void update();
	//void draw(ofEasyCam& cam);

	// Miscellaneous
	void addParticle(Particle* particle);
	void addBinding(Binding* binding);
	void addParticles(std::vector<Particle*> _particles);
	void addBindings(std::vector<Binding*> _bindings);

};

struct PhysicsEngine {
	static void updateScene(Scene* scene);
};


#endif
