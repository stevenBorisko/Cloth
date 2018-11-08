#include "Scene.hpp"

//----------------------------------------------------------------------------//
// --- Constructors --- //
//----------------------------------------------------------------------------//

SceneSwap::SceneSwap():
	particles(std::vector<ParticleSmall>())
{ }

SceneSwap::SceneSwap(const SceneSwap& other):
	SceneSwap()
{
	for(const auto& particle : other.particles)
		this->particles.emplace_back(particle);
}

SceneSwap::SceneSwap(const Scene& scene):
	SceneSwap()
{
	for(const auto& particle : scene.particles)
		this->particles.emplace_back(
			ParticleSmall(particle)
		);
}

SceneSwap::~SceneSwap() { }

//----------------------------------------------------------------------------//
// --- Operator Overloads --- //
//----------------------------------------------------------------------------//

SceneSwap& SceneSwap::operator=(const SceneSwap& rhs) {

	// get the vector to the right size

	while(this->particles.size() < rhs.particles.size())
		this->particles.emplace_back(ParticleSmall());
	while(this->particles.size() > rhs.particles.size())
		this->particles.pop_back();

	// copy the data in

	unsigned int i = 0;
	for(const auto& particle : rhs.particles)
		this->particles[i++] = particle;
	
	return *this;
}

SceneSwap& SceneSwap::operator=(const Scene& rhs) {

	// get the vector to the right size

	while(this->particles.size() < rhs.particles.size())
		this->particles.emplace_back(ParticleSmall());
	while(this->particles.size() > rhs.particles.size())
		this->particles.pop_back();

	// copy the data in

	unsigned int i = 0;
	for(const auto& particle : rhs.particles)
		this->particles[i++] = ParticleSmall(particle);
	
	return *this;
}

//----------------------------------------------------------------------------//
// --- Functions --- //
//----------------------------------------------------------------------------//

