#include "variable.h"

using namespace std;


class Ray {
public:
    vec3 ori;
    vec3 dir;

public:
    vec3 at(float t) const;
    Ray();
    Ray(float i, float j);

    Ray(const vec3 origin, const vec3 direction);
};


