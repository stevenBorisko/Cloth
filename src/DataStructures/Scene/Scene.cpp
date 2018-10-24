#include "Scene.hpp"

//----------------------------------------------------------------------------//
// Constructors //
//----------------------------------------------------------------------------//

Scene::Scene() :
	particles(std::vector<Particle*>()),
	bindings(std::vector<Binding*>()),
	globalGravity(0.0),
	tick(0)
{ }

Scene::Scene(const Scene& other):
	particles(other.particles),
	bindings(other.bindings),
	globalGravity(other.globalGravity),
	tick(0)
{ }

Scene::Scene(
	std::vector<Particle*> _particles,
	std::vector<Binding*> _bindings,
	const float& _globalGravity
):
	particles(_particles),
	bindings(_bindings),
	globalGravity(_globalGravity),
	tick(0)
{ }

Scene::~Scene() { }

//----------------------------------------------------------------------------//
// Operators //
//----------------------------------------------------------------------------//

Scene& Scene::operator=(const Scene& rhs) {
	this->particles = rhs.particles;
	this->bindings = rhs.bindings;
	this->globalGravity = rhs.globalGravity;
	this->tick = rhs.tick;
	return *this;
}

//----------------------------------------------------------------------------//
// Displayable Functions //
//----------------------------------------------------------------------------//

void Scene::setup() {
	for (auto& particle : this->particles)
		particle->setup();
	for (auto& binding : this->bindings)
		binding->setup();
}

void Scene::update() {
	PhysicsEngine::updateScene(this);
	for (auto& particle : this->particles)
		particle->update();
	for (auto& binding : this->bindings)
		binding->update();
}

/*
void Scene::draw(ofEasyCam& cam) {
	for (auto& particle : this->particles)
		particle->draw(cam);
	//for (auto& binding : this->bindings)
	//	binding->draw(cam);
}
*/

//----------------------------------------------------------------------------//
// Displayable Functions //
//----------------------------------------------------------------------------//

void Scene::addParticle(Particle* particle) {
	this->particles.emplace_back(particle);
}

void Scene::addBinding(Binding* binding) {
	this->bindings.emplace_back(binding);
}

void Scene::addParticles(std::vector<Particle*> _particles) {
	this->particles.insert(this->particles.end(), _particles.begin(), _particles.end());
}

void Scene::addBindings(std::vector<Binding*> _bindings) {
	this->bindings.insert(this->bindings.end(), _bindings.begin(), _bindings.end());
}
