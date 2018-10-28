#include "Scene.hpp"

//----------------------------------------------------------------------------//
// --- Constructors --- //
//----------------------------------------------------------------------------//

Scene::Scene() :
	particles(std::vector<Particle*>()),
	bindings(std::vector<Binding*>()),
	triangles(std::vector<Triangle*>()),
	globalGravity(0.0),
	visibility(0),
	tick(0)
{ }

Scene::Scene(const Scene& other):
	particles(other.particles),
	bindings(other.bindings),
	triangles(other.triangles),
	globalGravity(other.globalGravity),
	visibility(other.visibility),
	tick(0)
{ }

Scene::Scene(
	std::vector<Particle*> _particles,
	std::vector<Binding*> _bindings,
	std::vector<Triangle*> _triangles,
	const double& _globalGravity,
	const char& _visibility
):
	particles(_particles),
	bindings(_bindings),
	triangles(_triangles),
	globalGravity(_globalGravity),
	visibility(_visibility),
	tick(0)
{ }

Scene::~Scene() { }

//----------------------------------------------------------------------------//
// --- Operators --- //
//----------------------------------------------------------------------------//

Scene& Scene::operator=(const Scene& rhs) {
	this->particles = rhs.particles;
	this->bindings = rhs.bindings;
	this->triangles = rhs.triangles;
	this->globalGravity = rhs.globalGravity;
	this->visibility = rhs.visibility;
	this->tick = rhs.tick;
	return *this;
}

//----------------------------------------------------------------------------//
// --- Displayable Functions --- //
//----------------------------------------------------------------------------//

void Scene::update() {
	PhysicsEngine::updateScene(this);
	for (auto& particle : this->particles)
		particle->update();
	for (auto& binding : this->bindings)
		binding->update();
	for (auto& triangle : this->triangles)
		triangle->update();
}

void Scene::draw() {
	if(this->visibility & PARTICLES_VISIBLE)
		for(auto& particle : this->particles)
			particle->draw();
	if(this->visibility & PARTICLES_SIZE_VISIBLE)
		for(auto& particle : this->particles)
			if(particle->radius > 0.0)
				particle->draw();
	if(this->visibility & BINDINGS_VISIBLE)
		for(auto& binding : this->bindings)
			binding->draw();
	if(this->visibility & TRIANGLES_VISIBLE)
		for(auto& triangle : this->triangles)
			triangle->draw();
}

//----------------------------------------------------------------------------//
// --- Append --- //
//----------------------------------------------------------------------------//

void Scene::addParticle(Particle* particle) {
	this->particles.emplace_back(particle);
}

void Scene::addBinding(Binding* binding) {
	this->bindings.emplace_back(binding);
}

void Scene::addTriangle(Triangle* triangle) {
	this->triangles.emplace_back(triangle);
}

void Scene::addParticles(std::vector<Particle*> _particles) {
	this->particles.insert(this->particles.end(), _particles.begin(), _particles.end());
}

void Scene::addBindings(std::vector<Binding*> _bindings) {
	this->bindings.insert(this->bindings.end(), _bindings.begin(), _bindings.end());
}

void Scene::addTriangles(std::vector<Triangle*> _triangles) {
	this->triangles.insert(this->triangles.end(), _triangles.begin(), _triangles.end());
}
