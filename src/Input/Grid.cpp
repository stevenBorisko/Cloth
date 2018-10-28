#include "Input.hpp"

int Input::Grid(
	Scene* scene,
	const unsigned int& width,
	const unsigned int& space,
	const double& mass,
	const double& springConstant
) {

	// Particle stuff to be copied into scene at the end
	Particle*** mainGridParticles;
	Particle*** crossGridParticles;
	std::vector<Binding*> bindings;

	// other local variables
	int startY = (int)((width * space) >> 1);
	int startX = -startY;
	int startZ = 0;
	Vector4 position(0, 0, 0, 1);
	unsigned int i, j;

	//------------------------------------//
	// --- Particles --- //
	//------------------------------------//

	// Create memory for grid

	mainGridParticles = new Particle**[width];
	for (i = 0; i < width; ++i)
		mainGridParticles[i] = new Particle*[width];

	crossGridParticles = new Particle**[width - 1];
	for (i = 0; i < width - 1; ++i)
		crossGridParticles[i] = new Particle*[width - 1];

	// Create mainGridParticles
	startY += width * space;
	position = Vector4(startX, startY, startZ, 1);
	for (j = 0; j < width; ++j) {
		position[0] = (double)startX;
		for (i = 0; i < width; ++i) {
			mainGridParticles[j][i] = new Particle(1, position, Vector4(0,0,0,0), mass, 0.0f);
			position[0] += space;
		}
		position[1] -= space;
		position[2] += space;
	}

	// Create crossGridParticles
	double crossMass = mass * 0.1;
	startX += (space >> 1);
	startY -= (space >> 1);
	startZ += (space >> 1);
	position = Vector4(startX, startY, startZ, 1);
	for (j = 0; j < width - 1; ++j) {
		position[0] = (startX);
		for (i = 0; i < width - 1; ++i) {
			crossGridParticles[j][i] = new Particle(1, position, Vector4(0,0,0,0), crossMass, 0.0f);
			position[0] += space;
		}
		position[1] -= space;
		position[2] += space;
	}

	//------------------------------------//
	// --- Bindings --- //
	//------------------------------------//

	// longitudinal bindings
	for (j = 0; j < width - 1; ++j) {
		for (i = 0; i < width; ++i) {
			bindings.push_back(
				new Binding(
					mainGridParticles[j][i],
					mainGridParticles[j+1][i],
					springConstant,
					0
				)
			);
		}
	}

	// Lateral bindings
	for (j = 0; j < width; ++j) {
		for (i = 0; i < width - 1; ++i) {
			bindings.push_back(
				new Binding(
					mainGridParticles[j][i],
					mainGridParticles[j][i+1],
					springConstant,
					0
				)
			);
		}
	}

	// cross bindings
		// southeast
	double crossSpringConstant = springConstant * 1.2;
	for (j = 0; j < width - 1; ++j) {
		for (i = 0; i < width - 1; ++i) {
			bindings.emplace_back(
				new Binding(
					mainGridParticles[j][i],
					crossGridParticles[j][i],
					crossSpringConstant,
					0
				)
			);
			bindings.emplace_back(
				new Binding(
					crossGridParticles[j][i],
					mainGridParticles[j+1][i+1],
					crossSpringConstant,
					0
				)
			);
		}
	}
		// southwest
	for (j = 0; j < width - 1; ++j) {
		for (i = 1; i < width; ++i) {
			bindings.emplace_back(
				new Binding(
					mainGridParticles[j][i],
					crossGridParticles[j][i-1],
					crossSpringConstant,
					0
				)
			);
			bindings.emplace_back(
				new Binding(
					crossGridParticles[j][i-1],
					mainGridParticles[j+1][i-1],
					crossSpringConstant,
					0
				)
			);
		}
	}

	//------------------------------------//
	// --- Final Tweaks --- //
	//------------------------------------//

	mainGridParticles[0][0]->fixed = true;
	mainGridParticles[0][1]->fixed = true;
	mainGridParticles[1][0]->fixed = true;

	mainGridParticles[0][width - 1]->fixed = true;
	mainGridParticles[0][width - 2]->fixed = true;
	mainGridParticles[1][width - 1]->fixed = true;

	mainGridParticles[width - 1][0]->fixed = true;
	mainGridParticles[width - 2][0]->fixed = true;
	mainGridParticles[width - 1][1]->fixed = true;

	mainGridParticles[width - 1][width - 1]->fixed = true;
	mainGridParticles[width - 2][width - 1]->fixed = true;
	mainGridParticles[width - 1][width - 2]->fixed = true;

	for(i = 0;i < width;++i)
		mainGridParticles[0][i]->fixed = true;

	//------------------------------------//
	// --- Copy Data into Scene --- //
	//------------------------------------//

	for (j = 0; j < width; ++j)
		for (i = 0; i < width; ++i)
			scene->addParticle(mainGridParticles[j][i]);
	for (j = 0; j < width - 1; ++j)
		for (i = 0; i < width - 1; ++i)
			scene->addParticle(crossGridParticles[j][i]);
	scene->addBindings(bindings);

	//------------------------------------//
	// --- Free Memory --- //
	//------------------------------------//

	for (j = 0; j < width; ++j)
		delete[] mainGridParticles[j];
	delete[] mainGridParticles;
	for (j = 0; j < width - 1; ++j)
		delete[] crossGridParticles[j];
	delete[] crossGridParticles;

	return 0;
}
