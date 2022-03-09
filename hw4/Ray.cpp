#include "Ray.h"
Ray::Ray(){
	ori = vec3(0.0,0.0,0.0);
	dir = vec3(0.0, 0.0, 0.0);
}
Ray::Ray(const vec3 origin, const vec3 direction) {
	ori = origin;
	dir = direction;
}
   
Ray::Ray(int i, int j){
	vec3 u, w, v;
    w = glm::normalize(eye-center);
    u = glm::normalize(glm::cross(up, w));
    v = glm::cross(w, u);
	float alpha = (tanf(glm::radians(fovy) / 2.0) * (image_width / (image_height * 1.0))) * ((j - image_width / 2.0) / (image_width / 2.0));
	float beta = tanf(glm::radians(fovy) / 2.0) * ((image_height / 2.0 - i) / (image_height / 2.0));
	dir = normalize(alpha * u + beta * v - w);
	ori = eye;
}

vec3 Ray::at(float t) const
{
	return ori + t * dir;
}
