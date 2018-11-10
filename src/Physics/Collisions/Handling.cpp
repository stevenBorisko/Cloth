#include "../Physics.hpp"

double nearestFutureCollision(std::vector<Collision>& collisions) {
	double ret = 2.0; // A collision's intersection will never be more than 1.0
	for(const auto& collision : collisions)
		if(collision.future)
			ret = std::min(collision.intersection, ret);
	return ret;
}

double farthestFutureCollision(std::vector<Collision>& collisions) {
	double ret = -1.0; // A collision's intersection will never be less than 0.0
	for(const auto& collision : collisions)
		if(collision.future)
			ret = std::max(collision.intersection, ret);
	return ret;
}

void collisionSphereSphere(Scene* scene, const Collision& collision) {
}

void collisionSphereMesh(Scene* scene, const Collision& collision) {
}
