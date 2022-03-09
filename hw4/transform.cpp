// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "transform.h"

// Helper rotation function.  Please implement this.
mat3 Transform::rotate(const float degrees, const vec3 &axis)
{
    vec3 a = glm::normalize(axis);
    mat3 i(1.0f);
    i = i * glm::cos(degrees * pi / 180.0f);
    mat3 aat(a.x * a.x, a.x * a.y, a.x * a.z,
             a.x * a.y, a.y * a.y, a.y * a.z,
             a.x * a.z, a.y * a.z, a.z * a.z);
    aat = glm::transpose(aat);
    aat = (1 - glm::cos(degrees * pi / 180.0f)) * aat;
    mat3 A(0.0f, -a.z, a.y,
           a.z, 0.0f, -a.x,
           -a.y, a.x, 0.0f);
    A = glm::transpose(A);
    A = glm::sin(degrees * pi / 180.0f) * A;
    // You will change this return call
    return i + aat + A;
}

void Transform::left(float degrees, vec3 &eye, vec3 &up)
{
    // YOUR CODE FOR HW2 HERE
    // Likely the same as in HW 1.
    mat3 M = rotate(degrees, up);
    eye = M * eye;
    up = M * up;
}

void Transform::up(float degrees, vec3 &eye, vec3 &up)
{
    // YOUR CODE FOR HW2 HERE
    // Likely the same as in HW 1.
    vec3 axis = glm::cross(eye, up);
    mat3 M = rotate(degrees, axis);
    eye = M * eye;
    up = glm::transpose(glm::inverse(M)) * up;
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up)
{
    vec3 w = glm::normalize(eye - vec3(0.0f, 0.0f, 0.0f));
    vec3 u = glm::normalize(glm::cross(up, w));
    vec3 v = glm::cross(w, u);
    mat4 r(u.x, u.y, u.z, 0.0f,
           v.x, v.y, v.z, 0.0f,
           w.x, w.y, w.z, 0.0f,
           0.0f, 0.0f, 0.0f, 1.0f);
    r = glm::transpose(r);
    mat4 P = mat4(1.0f);
    P[0][3] = -1.0f * eye.x;
    P[1][3] = -1.0f * eye.y;
    P[2][3] = -1.0f * eye.z;
    P = glm::transpose(P);
    return r * P;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
    fovy = glm::radians(fovy);
    float deta = tanf(fovy / 2.0f);

    mat4 ret(0.0f);
    // YOUR CODE FOR HW2 HERE
    // New, to implement the perspective transform as well.
    ret[0][0] = 1.0f / (aspect * deta);
    ret[1][1] = 1.0f / deta;
    ret[3][2] = -1.0f;
    ret[2][2] = -(zFar + zNear) / (zFar - zNear);
    ret[2][3] = -(2.0f * zFar * zNear) / (zFar - zNear);
    ret = glm::transpose(ret);
    return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz)
{
    mat4 ret(1.0f);
    // YOUR CODE FOR HW2 HERE
    // Implement scaling
    ret[0][0] = sx;
    ret[1][1] = sy;
    ret[2][2] = sz;
    return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz)
{
    mat4 ret(1.0f);
    ret[0][3] = tx;
    ret[1][3] = ty;
    ret[2][3] = tz;
    // YOUR CODE FOR HW2 HERE
    // Implement translation
    return glm::transpose(ret);
}

// To normalize the up direction and construct a coordinate frame.
// As discussed in the lecture.  May be relevant to create a properly
// orthogonal and normalized up.
// This function is provided as a helper, in case you want to use it.
// Using this function (in readfile.cpp or display.cpp) is optional.

vec3 Transform::upvector(const vec3 &up, const vec3 &zvec)
{
    vec3 x = glm::cross(up, zvec);
    vec3 y = glm::cross(zvec, x);
    vec3 ret = glm::normalize(y);
    return ret;
}

Transform::Transform()
{
}

Transform::~Transform()
{
}
