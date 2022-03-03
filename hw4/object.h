#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>

using namespace std;

typedef glm::vec3 vec3;
typedef glm::vec4 vec4;
enum shape
{
    sphere,
    tri
};

class object
{
private:
    /* data */
    shape _type;
    vec4 _ambient;
    vec4 _diffuse;
    vec4 _specular;
    vec4 _emission;
    float _shininess;
public:
    object(const shape &type,
           float *ambient,
           float *diffuse,
           float *specular,
           float *emission,
           float &shininess);
};

class triangle: public object
{
private:
    /* data */
    vec3 _A;
    vec3 _B;
    vec3 _C;

public:
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
private:
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
           vec3 &C,
           float r);
};
