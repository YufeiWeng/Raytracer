#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>

using namespace std;

typedef glm::vec3 vec3;
typedef glm::vec4 vec4;
enum shape
{
    sph,
    tri
};

class object
{
public:
    /* data */
    shape _type;
    vec3 _ambient;
    vec3 _diffuse;
    vec3 _specular;
    vec3 _emission;
    float _shininess;

public:
    object(const shape& type,
        float* ambient,
        float* diffuse,
        float* specular,
        float* emission,
        float& shininess); //t is for the intersection point P such that P = ray.origin + t * ray.direction 
                  //default value will be positive infinity; see read file
};

class triangle: public object
{
public:
    /* data */


public:
    vec3 _A;
    vec3 _B;
    vec3 _C;
    triangle(const shape &type,
             float *ambient,
             float *diffuse,
             float *specular,
             float *emission,
             float &shininess,

             const vec3 &A_,
             const vec3 &B_,
             const vec3 &C_);
    // glm::vec3 hit(const Ray &ray);
};

class sphere : public object
{
public:
    /* data */
    vec3 _center;
    float _radius;

public:
    sphere(const shape &type,
           float *ambient,
           float *diffuse,
           float *specular,
           float *emission,
           float &shininess,
           const vec3 &C,
           float r);
};
