#include "Ray.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>  //If there are redlines, go and check: https://www.google.com/search?q=how+to+include+glm+in+visual+studio+2019&ei=tbkeYuH6BZrHkPIPgMex2A0&ved=0ahUKEwihqa6plab2AhWaI0QIHYBjDNsQ4dUDCA4&uact=5&oq=how+to+include+glm+in+visual+studio+2019&gs_lcp=Cgdnd3Mtd2l6EAMyBQghEKsCOgcIABBHELADOgYIABAWEB46BQgAEIYDOgUIIRCgAUoECEEYAEoECEYYAFCyBVj-C2D3DmgBcAF4AYAB9AGIAYcGkgEFMC40LjGYAQCgAQHIAQjAAQE&sclient=gws-wiz#kpvalbx=_u7keYvz9FrefkPIPt8SO8Aw20
using namespace std;
 

vec3 hit_triangle(const vec3 &vertexA,
                       const vec3 &vertexB, 
                       const vec3 &vertexC,
                       const Ray& ray) {
    vec3 normal = glm::cross((vertexC - vertexA), (vertexB - vertexA));
    normal = glm::normalize(normal);
    float t = (glm::dot(vertexA, normal) - glm::dot(ray.ori, normal)) / (glm::dot(ray.dir,normal));
    glm::vec3 P = ray.at(t);
    if (glm::dot(ray.dir, normal) == 0) {
        return vec3(0.0, 0.0, 0.0);
    }

    vec3 Apnormal, Bpnormal, Cpnormal;
    Apnormal = (glm::cross(normal, vertexC-vertexB))/
                glm::dot((glm::cross(normal, vertexC - vertexB)), vertexA-vertexC);

}

vec3 hit_sphere(const vec3& center, double radius, const Ray& ray ) {
    //at^2+bt+c=0
    //d=sqrt(b^2-4ac)
    //t=(-b+-d)/(2a)
    float a = glm::dot(ray.dir, ray.dir);
    float b = 2.0 * glm::dot(ray.dir, ray.ori - center);
    float c = glm::dot(ray.ori - center, ray.ori - center) - radius * radius;
    float d = b * b - 4.0 * a * c;
    //two intersections
    if (d > 0) {
        //red for now
        return vec3(1.0, 0.0, 0.0);
    }
    //one or none
    else {
        //background is black
        return vec3(0.0, 0.0, 0.0);
    }
}


int main(int argc, char* argv[]) {

    //uwv

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int i = 0; i < image_height; ++i) {
        for (int j = 0; j < image_width; ++j) {
            Ray ray(i, j);
            vec3 color = hit_sphere(vec3(0,0,0), 0.5, ray);
            cout << static_cast<int>(255.999 * color.x) << ' '
                << static_cast<int>(255.999 * color.y) << ' '
                << static_cast<int>(255.999 * color.z) << '\n';
        }
    }
    return 0;
}

