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
	const double& _globalGravity
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

void Scene::update(Scene* swap) {
	PhysicsEngine::updateScene(this,swap);
	for (auto& particle : this->particles)
		particle->update();
	for (auto& binding : this->bindings)
		binding->update();
}

void Scene::draw() {
	for (auto& particle : this->particles)
		particle->draw();
	for (auto& binding : this->bindings)
		binding->draw();
}

//----------------------------------------------------------------------------//
// Miscellaneous //
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
//----------------------------------------------------------------------------//
// Copying //
//----------------------------------------------------------------------------//

void Scene::deepCopyFrom(const Scene* other) {
	unsigned int i;
	this->globalGravity = other->globalGravity;
	this->tick = other->tick;
	// Ensure vectors are the same size
	if(this->particles.size() != other->particles.size()) {
		while(this->particles.size() < other->particles.size())
			this->particles.emplace_back(new Particle);
		while(this->particles.size() > other->particles.size()) {
			delete this->particles.back();
			this->particles.pop_back();
		}
	}
	if(this->bindings.size() != other->bindings.size()) {
		while(this->bindings.size() < other->bindings.size())
			this->bindings.emplace_back(new Binding);
		while(this->bindings.size() > other->bindings.size()) {
			delete this->bindings.back();
			this->bindings.pop_back();
		}
	}

	// Copy data
	i = 0;
	for(auto& particle : other->particles)
		*this->particles[i++] = *particle;
	i = 0;
	for(auto& binding : other->bindings)
		*this->bindings[i++] = *binding;
}

void Scene::deepCopyInto(Scene* other) const {
	other->deepCopyFrom(this);
}
