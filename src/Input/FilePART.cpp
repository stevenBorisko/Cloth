#include "Input.hpp"

//----------------------------------------------------------------------------//
// --- Helper Function Declaration --- //
//----------------------------------------------------------------------------//

/*
Format: `<lineType> [parameters]`
- lineType (char):
	v: velocity
	p: particle
	b: binding
*/
int readLine(
	std::vector<Vector4>& velocities,
	std::vector<Particle*>& particles,
	std::vector<Binding*>& bindings,
	std::istringstream& lineStream
);

/*
Format: `v <x> <y> <z>`
- x (double):
	x value of the initial velocity of a particle
- y (double):
	y value of the initial velocity of a particle
- z (double):
	z value of the initial velocity of a particle
*/
int readVelocity(
	std::vector<Vector4>& velocities,
	std::istringstream& lineStream
);

/*
Format: `p <x> <y> <z> <vIndex> <mass> <dynamic>`
- x (double):
	x value of the initial position of the particle
- y (double):
	y value of the initial position of the particle
- z (double):
	z value of the initial position of the particle
- vIndex (int):
	Index of the initial velocity
- mass (double):
	Mass of the particle
- dynamic (int):
	0 - particle is static
	1 - particle is dynamic
*/
int readParticle(
	const std::vector<Vector4>& velocities,
	std::vector<Particle*>& particles,
	std::istringstream& lineStream
);

/*
Format: `b <p0> <p1> <springConstant> <dynamic> <initStretch>`
- p0 (int):
	index of particle to bind to p1
- p1 (int):
	Index of particle to bind to p0
- springConstant (double):
	Physical spring
- dynamic (int):
	0 - binding is static
	1 - binding is dynamic
- initStretch (double):
	How much the binding is stretched initially
	Can be negative if is compressed initially
	Not necessary if `dynamic` is 0
*/
int readBinding(
	std::vector<Particle*>& particles,
	std::vector<Binding*>& bindings,
	std::istringstream& lineStream
);

//----------------------------------------------------------------------------//
// --- Input Function Implementation --- //
//----------------------------------------------------------------------------//

int Input::FilePART(Scene* scene, std::ifstream& file) {

	// --- Retrieve data from file --- //

	std::vector<Vector4> velocities;
	std::vector<Particle*> particles;
	std::vector<Binding*> bindings;

	unsigned int lineNumber;
	std::string line;

	for(lineNumber = 1; std::getline(file,line); ++lineNumber) {
		std::cerr << "reading line\n";
		std::istringstream lineStream(line);
		int err = readLine(velocities,particles,bindings,lineStream);
		lineStream.clear();
		if(err) {
			std::cerr << "Error on line " << lineNumber << "\n\t";
			switch(err) {
			case 1:
				std::cerr << "Line unreadable";
				break;
			case 2:
				std::cerr << "Unknown type";
				break;
			default:
				break;
			}
			std::cerr << "\n";
			return lineNumber;
		}
	}

	// --- Give data back to scene --- //
	scene->addParticles(particles);
	scene->addBindings(bindings);

	return 0;
}

//----------------------------------------------------------------------------//
// --- Helper Function Implementation --- //
//----------------------------------------------------------------------------//

int readLine(
	std::vector<Vector4>& velocities,
	std::vector<Particle*>& particles,
	std::vector<Binding*>& bindings,
	std::istringstream& lineStream
) {
	std::string lineType;
	if(!(lineStream >> lineType))
		return 1;
	if(!lineType.compare("#"))
		return 0;
	if(!lineType.compare("v"))
		return readVelocity(velocities,lineStream);
	if(!lineType.compare("p")) 
		return readParticle(velocities,particles,lineStream);
	if(!lineType.compare("b"))
		return readBinding(particles,bindings,lineStream);
	return 2;
}

int readVelocity(
	std::vector<Vector4>& velocities,
	std::istringstream& lineStream
) {
	double vx, vy, vz;

	if(!(lineStream >> vx >> vy >> vz)) return 1;
	velocities.push_back(Vector4(vx,vy,vz,0));

	return 0;
}

int readParticle(
	const std::vector<Vector4>& velocities,
	std::vector<Particle*>& particles,
	std::istringstream& lineStream
) {

	double px, py, pz, mass;
	int vIndex, dynamic;
	if(!(lineStream >> px >> py >> pz >> vIndex >> mass >> dynamic)) return 1;

	particles.emplace_back(
		new Particle(
			dynamic, Vector4(px,py,pz,0), velocities[vIndex], mass, 10
		)
	);

	return 0;
}

int readBinding(
	std::vector<Particle*>& particles,
	std::vector<Binding*>& bindings,
	std::istringstream& lineStream
) {

	unsigned int particle0, particle1, dynamic;
	double initStretch, springConstant;
	lineStream >> particle0 >> particle1 >> springConstant >> dynamic;

	if(dynamic) {
		if(!(lineStream >> initStretch)) return 1;
		bindings.emplace_back(
			new Binding(
				particles[particle0],
				particles[particle1],
				springConstant,
				initStretch
			)
		);
	} else {
		bindings.emplace_back(
			new Binding(
				particles[particle0],
				particles[particle1],
				springConstant
			)
		);
	}

	return 0;
}
