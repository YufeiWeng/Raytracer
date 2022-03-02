#include "Ray.h"



Ray(const glm::vec3& origin, const glm::vec3& direction) {
	ori = origin;
	dir = direction;
}


void at(double t) {
	return ori + t * dir;
}


