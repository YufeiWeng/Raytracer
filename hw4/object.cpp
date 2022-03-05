#include "object.h"

object::object(const shape &type,
               float *ambient,
               float *diffuse,
               float *specular,
               float *emission,
               float &shininess)
{
    _type=type;
    _ambient[0] = ambient[0];
    _ambient[1] = ambient[1];
    _ambient[2] = ambient[2];
    //_ambient[3] = 1.0;
    _diffuse[0] = diffuse[0];
    _diffuse[1] = diffuse[1];
    _diffuse[2] = diffuse[2];
    //_diffuse[3] = 1.0;
    _specular[0] = specular[0];
    _specular[1] = specular[1];
    _specular[2] = specular[2];
    //_specular[3] = 1.0;
    _emission[0] = emission[0];
    _emission[1] = emission[1];
    _emission[2] = emission[2];
    //_emission[3] = 1.0;
    _shininess = shininess;

}

triangle::triangle(const shape &type,
                   float *ambient,
                   float *diffuse,
                   float *specular,
                   float *emission,
                   float &shininess,

                   const vec3 &A_,
                   const vec3 &B_,
                   const vec3 &C_) : object(type,
                                          ambient,
                                          diffuse,
                                          specular,
                                          emission,
                                          shininess
                                          )
{


    _A=A_;
    _B=B_;
    _C=C_;

}
vec3 triangle::findNormal() {
    vec3 normal = cross((this->_C - this->_A), (this->_B - this->_A));
    normal = glm::normalize(normal);
    return normal;
}


sphere::sphere(const shape &type,
               float *ambient,
               float *diffuse,
               float *specular,
               float *emission,
               float &shininess,
               const vec3 &C,
               float r) : object(type,
                                 ambient,
                                 diffuse,
                                 specular,
                                 emission,
                                 shininess
                                 )
{
    _center=C;
    _radius=r;
}
