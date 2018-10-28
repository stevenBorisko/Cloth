#include "Scene.hpp"

//----------------------------------------------------------------------------//
// Constructors //
//----------------------------------------------------------------------------//

Scene::Scene() :
	particles(std::vector<Particle*>()),
	bindings(std::vector<Binding*>()),
	triangles(std::vector<Triangle*>()),
	globalGravity(0.0),
	tick(0)
{ }

Scene::Scene(const Scene& other):
	particles(other.particles),
	bindings(other.bindings),
	triangles(other.triangles),
	globalGravity(other.globalGravity),
	tick(0)
{ }

Scene::Scene(
	std::vector<Particle*> _particles,
	std::vector<Binding*> _bindings,
	std::vector<Triangle*> _triangles,
	const double& _globalGravity
):
	particles(_particles),
	bindings(_bindings),
	triangles(_triangles),
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
	this->triangles = rhs.triangles;
	this->globalGravity = rhs.globalGravity;
	this->tick = rhs.tick;
	return *this;
}

//----------------------------------------------------------------------------//
// Displayable Functions //
//----------------------------------------------------------------------------//

void Scene::update(Scene* swap) {
	PhysicsEngine::updateScene(this,swap);
	for (auto& particle : this->particles)
		particle->update();
	for (auto& binding : this->bindings)
		binding->update();
	for (auto& triangle : this->triangles)
		triangle->update();
}

void Scene::draw() {
	for (auto& particle : this->particles)
		particle->draw();
	for (auto& binding : this->bindings)
		binding->draw();
	for (auto& triangle : this->triangles)
		triangle->draw();
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
	if(this->triangles.size() != other->triangles.size()) {
		while(this->triangles.size() < other->triangles.size())
			this->triangles.emplace_back(new Triangle);
		while(this->triangles.size() > other->triangles.size()) {
			delete this->triangles.back();
			this->triangles.pop_back();
		}
	}

	// Copy data
	i = 0;
	for(auto& particle : other->particles)
		*this->particles[i++] = *particle;
	i = 0;
	for(auto& binding : other->bindings)
		*this->bindings[i++] = *binding;
	i = 0;
	for(auto& triangle : other->triangles)
		*this->triangles[i++] = *triangle;
}

void Scene::deepCopyInto(Scene* other) const {
	other->deepCopyFrom(this);
}
