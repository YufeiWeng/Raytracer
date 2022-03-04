
#define MAINPROGRAM 
#include "Ray.h"
#include "readfile.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>  //If there are redlines, go and check: https://www.google.com/search?q=how+to+include+glm+in+visual+studio+2019&ei=tbkeYuH6BZrHkPIPgMex2A0&ved=0ahUKEwihqa6plab2AhWaI0QIHYBjDNsQ4dUDCA4&uact=5&oq=how+to+include+glm+in+visual+studio+2019&gs_lcp=Cgdnd3Mtd2l6EAMyBQghEKsCOgcIABBHELADOgYIABAWEB46BQgAEIYDOgUIIRCgAUoECEEYAEoECEYYAFCyBVj-C2D3DmgBcAF4AYAB9AGIAYcGkgEFMC40LjGYAQCgAQHIAQjAAQE&sclient=gws-wiz#kpvalbx=_u7keYvz9FrefkPIPt8SO8Aw20


/*
* Return a boolean: If ray hit tri, then ture; Also update tri's t
*/
bool hit_triangle(triangle* tri,const Ray& ray) {
    const vec3 vertexA = tri->_A;
    const vec3 vertexB = tri->_B; 
    const vec3 vertexC = tri->_C;
    vec3 normal = glm::cross((vertexC - vertexA), (vertexB - vertexA));
    normal = glm::normalize(normal);
    float t = (glm::dot(vertexA, normal) - glm::dot(ray.ori, normal)) / (glm::dot(ray.dir, normal));
    glm::vec3 P = ray.at(t);
    if (glm::dot(ray.dir, normal) == 0) {
        return false;
    }

    vec3 Apnormal, Bpnormal, Cpnormal;
    Apnormal = (glm::cross(normal, vertexC - vertexB)) /
        glm::dot((glm::cross(normal, vertexC - vertexB)), vertexA - vertexC);
    Bpnormal = (glm::cross(normal, vertexA - vertexC)) /
        glm::dot((glm::cross(normal, vertexA - vertexC)), vertexB - vertexA);
    Cpnormal = (glm::cross(normal, vertexB - vertexA)) /
        glm::dot((glm::cross(normal, vertexB - vertexA)), vertexC - vertexB);
    float Apw = glm::dot(-Apnormal, vertexC);
    float Bpw = glm::dot(-Bpnormal, vertexA);
    float Cpw = glm::dot(-Cpnormal, vertexB);

    float a, b, c;
    a = glm::dot(Apnormal, P) + Apw;
    b = glm::dot(Bpnormal, P) + Bpw;
    c = glm::dot(Cpnormal, P) + Cpw;

    // if (a >= 0.0 && b >= 0.0 && c >= 0.0 && a + b + c == 1.0) {
    //     return vec3(1.0, 0.0, 0.0);
    // }
    // else {
    //     return vec3(0.0, 0.0, 0.0);
    // }

    if (a < 0) {
        return false;
    }
    if (a > 1) {
        return false;
    }
    if (b < 0) {
        return false;
    }
    if (b > 1) {
        return false;
    }
    if (c < 0) {
        return false;
    }
    if (c > 1) {
        return false;
    }
    tri->_t = t;
    return true;
}

// very similar to hit_triangle
bool hit_sphere(sphere* sph, const Ray& ray) {//remember to return an pointer of object
    //at^2+bt+c=0
    //d=b^2-4ac
    //t=(-b+-sqrt(d))/(2a)
    const vec3 center = sph->_center; 
    double radius = sph->_radius;
    float a = glm::dot(ray.dir, ray.dir);
    float b = 2.0 * glm::dot(ray.dir, ray.ori - center);
    float c = glm::dot(ray.ori - center, ray.ori - center) - radius * radius;
    float d = b * b - 4.0 * a * c;
    //two intersections
    if (d > 0) {
        float t1 = (-b - sqrt(d)) / (2 * a);
        float t2 = (-b + sqrt(d)) / (2 * a);
        //two positive roots; keep smaller
        if (t1 > 0 && t2 > 0) {
            sph->_t = min(t1, t2);
            return true;
        }
        //one negative one positive; keep positive
        else if (t1 < 0 && t2 > 0) {
            sph->_t = t2;
            return true;
        }
        else if (t1 > 0 && t2 < 0) {
            sph->_t = t1;
            return true;
        }
        //two identical postive roots
        else if (t1 == t2 && t1 > 0) {
            sph->_t = t1;
            return true;
        }
        else {
            return false;
        }
    }
    //one or none
    else {
        //background is black
        return false;
    }
}

/*
* return the clostest object 
*/
object* Intersection(vector<object*> obj, Ray& ray) {
    float t_min = obj[0]->_t;
    object* closest = nullptr;
    for (int k = 0; k < obj.size(); k++) {
        if (obj[k]->_type == tri) {
            triangle* tri = (triangle*)obj[k];// how to get tri
            //check if ray hits the tri
            if (hit_triangle(tri, ray)) {
                //if tri is closer
                if (tri->_t < t_min) {
                    closest = tri;
                    t_min = tri->_t;//update t_min
                }
            }
        }
        else {
            sphere* sph = (sphere*)obj[k];
            if (hit_sphere(sph, ray)) {
                //if sph is closer
                if (sph->_t < t_min) {
                    closest = sph;
                    t_min = sph->_t;//update t_min
                }
            }
        }
    }
    return closest;
}

/*
*compute color; need further implements
*/
vec3 ComputeColor(object* obj) {
    return obj->_ambient;
}



int main(int argc, char* argv[]) {

    //uwv

    // Render
    // cout<<argv[1]<<endl;

    // cout<<(triangle)obj[0]<<endl;
    readfile(argv[1]);

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    // cout<<obj[1]->_type<<endl;
    for (int i = 0; i < image_height; ++i) {
        for (int j = 0; j < image_width; ++j) {
            Ray ray(i, j);
            vec3 color(0.0,0.0,0.0);
            //vec3 color = hit_sphere(vec3(0,0,0), 0.5, ray);
            //vec3 color = hit_triangle(A, B, C, ray);
            object* hit = Intersection(obj, ray);
            color = ComputeColor(hit);
            cout << static_cast<int>(255.999 * color.x) << ' '
                  << static_cast<int>(255.999 * color.y) << ' '
                  << static_cast<int>(255.999 * color.z) << '\n';
        }
    }
    int i = 0;
    while (i < obj.size())
    {
        delete obj.back();
        obj.pop_back(); 
        i++;
    }
    
    return 0;
}
