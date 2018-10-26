#ifndef INPUT_H
#define INPUT_H

#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <sstream>

#include "../DataStructures/Scene/Scene.hpp"

struct Input {

	static int FilePART(Scene* scene, std::ifstream& file);
	static int Grid(
		Scene* scene,
		const unsigned int& width,
		const unsigned int& space,
		const double& mass,
		const double& springConstant
	);

};

#endif
