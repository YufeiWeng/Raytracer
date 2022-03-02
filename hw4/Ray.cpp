#include "Ray.h"

glm::vec3 ori;
glm::vec3 dir;


Ray(const glm::vec3 &origin, const glm::vec3 &direction) {
	ori = origin;
	dir = direction;
}


void at(double t) const {
	return ori + t * dir;
}


