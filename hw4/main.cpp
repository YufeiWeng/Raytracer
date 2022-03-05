
#define MAINPROGRAM
#include "Ray.h"
#include "readfile.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> //If there are redlines, go and check: https://www.google.com/search?q=how+to+include+glm+in+visual+studio+2019&ei=tbkeYuH6BZrHkPIPgMex2A0&ved=0ahUKEwihqa6plab2AhWaI0QIHYBjDNsQ4dUDCA4&uact=5&oq=how+to+include+glm+in+visual+studio+2019&gs_lcp=Cgdnd3Mtd2l6EAMyBQghEKsCOgcIABBHELADOgYIABAWEB46BQgAEIYDOgUIIRCgAUoECEEYAEoECEYYAFCyBVj-C2D3DmgBcAF4AYAB9AGIAYcGkgEFMC40LjGYAQCgAQHIAQjAAQE&sclient=gws-wiz#kpvalbx=_u7keYvz9FrefkPIPt8SO8Aw20

/*
 * Return a boolean: If ray hit tri, then ture; Also update tri's t
 */
float hit_triangle(triangle *tri, const Ray &ray)
{
    const vec3 vertexA = tri->_A;
    const vec3 vertexB = tri->_B;
    const vec3 vertexC = tri->_C;
    vec3 normal = glm::cross((vertexC - vertexA), (vertexB - vertexA));
    normal = glm::normalize(normal);
    float t = (glm::dot(vertexA, normal) - glm::dot(ray.ori, normal)) / (glm::dot(ray.dir, normal));
    glm::vec3 P = ray.at(t);
    if (glm::dot(ray.dir, normal) == 0)
    {
        return -1;
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

    if (a < 0)
    {
        return -1.0;
    }
    if (a > 1)
    {
        return -1.0;
    }
    if (b < 0)
    {
        return -1.0;
    }
    if (b > 1)
    {
        return -1.0;
    }
    if (c < 0)
    {
        return -1.0;
    }
    if (c > 1)
    {
        return -1.0;
    }

    return t;
}

// very similar to hit_triangle
float hit_sphere(sphere *sph, const Ray &ray)
{ // remember to return an pointer of object
    // at^2+bt+c=0
    // d=b^2-4ac
    // t=(-b+-sqrt(d))/(2a)
    const vec3 center = sph->_center;
    double radius = sph->_radius;
    float a = glm::dot(ray.dir, ray.dir);
    float b = 2.0 * glm::dot(ray.dir, ray.ori - center);
    float c = glm::dot(ray.ori - center, ray.ori - center) - radius * radius;
    float d = b * b - 4.0 * a * c;
    // two intersections
    if (d > 0)
    {
        float t1 = (-b - sqrt(d)) / (2 * a);
        float t2 = (-b + sqrt(d)) / (2 * a);
        // two positive roots; keep smaller
        if (t1 > 0 && t2 > 0)
        {

            return min(t1, t2);
        }
        // one negative one positive; keep positive
        else if (t1 < 0 && t2 > 0)
        {

            return t2;
        }
        else if (t1 > 0 && t2 < 0)
        {

            return t1;
        }
        // two identical postive roots
        else if (t1 == t2 && t1 > 0)
        {

            return t1;
        }
        else
        {
            return -1.0;
        }
    }
    // one or none
    else
    {
        // background is black
        return -1.0;
    }
}

/*
 * return the clostest object
 */
hit_record Intersection(const vector<object *> &objList,const Ray &ray)
{
    float t_min = INF;
    object *closest = nullptr;
    hit_record output;
    output.t=-1.0;
    for (int k = 0; k < objList.size(); k++)
    {
        if (objList[k]->_type == tri)
        {
            triangle *tri = (triangle *)objList[k]; // how to get tri
            // check if ray hits the tri
            float t_value = hit_triangle(tri, ray);

            // if tri is closer
            if (t_value < t_min && t_value > 0)
            {

                closest = tri;
                t_min = t_value; // update t_min
                output.target = closest;
                output.t=t_min;
            }
        }
        else
        {
            sphere *sph = (sphere *)objList[k];
            float t_value = hit_sphere(sph, ray);

            // if sph is closer
            if (t_value < t_min && t_value > 0)
            {
                closest = sph;
                t_min = t_value; // update t_min
                output.target = closest;
                output.t = t_min;
            }
        }
    }
    output.p=ray;
    return output;
}




/*
 *compute color; need further implements
 */
vec3 ComputeColor(hit_record *closest)
{
    vec3 finalcolor(0.0, 0.0, 0.0);
    if (closest == nullptr)
    {
        return finalcolor;
    }
    else
    {
        // cout << "notnull" << endl;
        // return vec3(1.0, 0.0, 0.0);
        vec3 normal;
        if (closest->_type == tri) {
            triangle* tri = (triangle*)closest;
            normal = tri->findNormal();
        }
        for (int i = 0; i < numused; i++) {
            vec3 eyedirn = ray.dir; //???
            vec3 diffuse = closest->_diffuse;
            vec3 specular = closest->_specular;
            float shininess = closest->_shininess;
            vec3 position;
            vec3 direction;
            vec3 myhalf;
            vec4 color = vec4(lightcolor[4*i], lightcolor[4*i+1], lightcolor[4 * i + 2], lightcolor[4 * i + 3]);
            vec4 lightposn = vec4(lightposn[4 * i], lightposn[4 * i + 1], lightposn[4 * i + 2], lightposn[4 * i + 3]);
            if (lightposn.w == 0) {   //directional 
                direction = vec3(lightposn[4 * i], lightposn[4 * i + 1], lightposn[4 * i + 2]);
                direction = normalize(direction);
                myhalf = normalize(direction + eyedirn);
            }
            else {     //point???
                position = lightposn[i].xyz / lightposn[i].w;
                direction = normalize(position - mypos);
                myhalf = normalize(direction + eyedirn);
            }
            vec3 col = ComputeLight(direction, color, normal, myhalf, diffuse, specular, shininess);
            finalcolor += color;
        }


        finalcolor += ambient;
        return finalcolor;
    }
}

vec3 ComputeLight(const vec3 direction, const vec3 lightcolor, const vec3 normal, const vec3 halfvec, const vec3 mydiffuse, const vec3 myspecular, const float myshininess) {

    float nDotL = dot(normal, direction);
    vec3 lambert = mydiffuse * lightcolor * max(nDotL, float(0.0));

    float nDotH = dot(normal, halfvec);
    vec3 phong = myspecular * lightcolor * pow(max(nDotH, float(0.0)), myshininess);

    vec3 retval = lambert + phong;
    return retval;
}

int main(int argc, char *argv[])
{

    // uwv

    // Render
    // cout<<argv[1]<<endl;

    // cout<<(triangle)obj[0]<<endl;
    readfile(argv[1]);

    std::cout << "P3\n"
              << image_width << ' ' << image_height << "\n255\n";
    // cout<<obj[1]->_type<<endl;
    for (int i = 0; i < image_height; ++i)
    {
        for (int j = 0; j < image_width; ++j)
        {
            Ray ray(i, j);
            vec3 color(0.0, 0.0, 0.0);
            hit_record hit = Intersection(obj, ray);
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
