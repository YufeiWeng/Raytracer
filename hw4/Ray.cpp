#include "Ray.h"

Ray::Ray(const glm::vec3 origin, const glm::vec3 direction) {
	ori = origin;
	dir = direction;
}


glm::vec3 Ray::at(double t) const {
	return ori + float(t) * dir;
}


