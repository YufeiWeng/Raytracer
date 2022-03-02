#include "variable.h"

using namespace std;


class Ray {
public:
    vec3 ori;
    vec3 dir;

public:
    vec3 at(double t) const;
    Ray(int i, int j);

    Ray(const vec3 origin, const vec3 direction);
};


