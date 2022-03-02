#include "main.h"
#include "Ray.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>  //If there are redlines, go and check: https://www.google.com/search?q=how+to+include+glm+in+visual+studio+2019&ei=tbkeYuH6BZrHkPIPgMex2A0&ved=0ahUKEwihqa6plab2AhWaI0QIHYBjDNsQ4dUDCA4&uact=5&oq=how+to+include+glm+in+visual+studio+2019&gs_lcp=Cgdnd3Mtd2l6EAMyBQghEKsCOgcIABBHELADOgYIABAWEB46BQgAEIYDOgUIIRCgAUoECEEYAEoECEYYAFCyBVj-C2D3DmgBcAF4AYAB9AGIAYcGkgEFMC40LjGYAQCgAQHIAQjAAQE&sclient=gws-wiz#kpvalbx=_u7keYvz9FrefkPIPt8SO8Aw20
using namespace std;


glm::vec3 hit_sphere(const glm::vec3& center, double radius, const Ray& ray ) {
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
        return glm::vec3(1.0, 0.0, 0.0);
    }
    //one or none
    else {
        //background is black
        return glm::vec3(0.0, 0.0, 0.0);
    }
}


int main(int argc, char* argv[]) {

    // Image

    const int image_width = 640; //from test scene 
    const int image_height = 480;
    const float ratio = image_width / image_height;

    // Camera
    glm::vec3 eye(-4, -4, 4); //0 for now 
    glm::vec3 center(0.0, 1.0, 0.0);
    float fovy(30);
    float fovx= fovy * ratio;
    glm::vec3 up(1.0, 0.0, 0.0);


    //uwv
    glm::vec3 u, w, v;
    w = glm::normalize(eye);
    u = glm::normalize(glm::cross(up, w));
    v = glm::cross(w, u);

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int i = 0; i < image_height; ++i) {
        for (int j = 0; j < image_width; ++j) {
            float alpha = tanf(glm::radians(fovx) / 2.0) * ((j - image_width / 2.0) / (image_width / 2.0));
            float beta = tanf(glm::radians(fovy) / 2.0) * ((image_height / 2.0 - i) / (image_height / 2.0));
            glm::vec3 direction = normalize(alpha * u + beta * v - w);
            Ray ray(eye, direction);
            glm::vec3 color = hit_sphere(glm::vec3(0,0,0), 0.5, ray);
            cout << static_cast<int>(255.999 * color.x) << ' '
                << static_cast<int>(255.999 * color.y) << ' '
                << static_cast<int>(255.999 * color.z) << '\n';
        }
    }
    return 0;
}

