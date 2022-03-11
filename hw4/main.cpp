
#define MAINPROGRAM
#include "Ray.h"
#include "readfile.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp> //If there are redlines, go and check: https://www.google.com/search?q=how+to+include+glm+in+visual+studio+2019&ei=tbkeYuH6BZrHkPIPgMex2A0&ved=0ahUKEwihqa6plab2AhWaI0QIHYBjDNsQ4dUDCA4&uact=5&oq=how+to+include+glm+in+visual+studio+2019&gs_lcp=Cgdnd3Mtd2l6EAMyBQghEKsCOgcIABBHELADOgYIABAWEB46BQgAEIYDOgUIIRCgAUoECEEYAEoECEYYAFCyBVj-C2D3DmgBcAF4AYAB9AGIAYcGkgEFMC40LjGYAQCgAQHIAQjAAQE&sclient=gws-wiz#kpvalbx=_u7keYvz9FrefkPIPt8SO8Aw20
struct hit_record
{
    Ray p;
    float t;
    vec3 point;
    object *target;
};
/*
 * Return a boolean
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
hit_record Intersection(const vector<object *> &objList, const Ray &ray)
{
    float t_min = INF;
    object *closest = nullptr;
    hit_record output;
    output.t = -1.0;
    for (int k = 0; k < objList.size(); k++)
    {

        vec3 newdir = vec3(inverse(objList[k]->_transform) * vec4(ray.dir, 0.0f));
        vec3 newori = vec3(inverse(objList[k]->_transform) * vec4(ray.ori, 1.0f));
        // if (k == 12)
        // {   
        //     cout<<"ori "<<glm::to_string(ray.dir)<<endl;
        //     std::cout << glm::to_string(inverse(objList[k]->_transform)) << std::endl;
        //     cout << "new " << glm::to_string(inverse(objList[k]->_transform) * vec4(ray.dir, 0.0f)) << endl;
        // }
        Ray newray;
        vec3 pointBefore;
        newray.dir=newdir; newray.ori=newori;
        if (objList[k]->_type == tri)
        {
            triangle *tri = (triangle *)objList[k]; // how to get tri
            // check if ray hits the tri
            float t_value = hit_triangle(tri, newray);

            // if tri is closer
            if (t_value < t_min && t_value > 0)
            {

                closest = tri;
                t_min = t_value; // update t_min
                output.target = closest;
                output.t = t_min;
                output.point=newray.ori+newray.dir*output.t;
            }
        }
        else
        {
            sphere *sph = (sphere *)objList[k];
            float t_value = hit_sphere(sph, newray);

            // if sph is closer
            if (t_value < t_min && t_value > 0)
            {
                closest = sph;
                t_min = t_value; // update t_min
                output.target = closest;
                output.t = t_min;
                output.point = newray.ori + newray.dir * output.t;
            }
        }
    }
    output.p = ray;
    
    return output;
}

vec3 ComputeLight(const vec3 direction, const vec3 lightcolor, const vec3 normal, const vec3 halfvec, const vec3 mydiffuse, const vec3 myspecular, const float myshininess)
{

    float nDotL = dot(normal, direction);
    vec3 lambert = mydiffuse * lightcolor * max(nDotL, float(0.0));

    float nDotH = dot(normal, halfvec);
    vec3 phong = myspecular * lightcolor * pow(max(nDotH, float(0.0)), myshininess);

    vec3 retval = lambert + phong;
    // cout << nDotL << endl;
    // cout << lambert[0] << lambert[1] <<" "<< lambert[2] << endl;
    return retval;
}

//if shadow return 0
float computeV(vec3& intP, vec4& lightDir) {
    Ray ray;
    //if directional
    if (lightDir[3] == 0) {
        ray.dir = normalize(vec3(lightDir[0], lightDir[1], lightDir[2]));
        ray.ori = intP+ (float(0.001) * ray.dir);
        hit_record h = Intersection(obj, ray);
        if (h.t == -1) {
            return 1.0;
        }
        else {
            return 0.0;
        }
    }
    //point
    else {
        ray.dir = normalize(vec3(lightDir) - intP);
        ray.ori = intP + (float(0.001) * ray.dir);
        hit_record h = Intersection(obj, ray);
        float t_between = distance(ray.ori, vec3(lightDir[0], lightDir[1], lightDir[2]));
        if (h.t == -1 || t_between < h.t ) {
            return 1.0;
        }
        else {
            return 0.0;
        }
    }
    

}

/*
 *compute color; need further implements
 */
vec3 ComputeColor(hit_record closest)
{
    vec3 finalcolor(0.0, 0.0, 0.0);
    if (closest.t < 0)
    {
        return finalcolor;
    }
    else
    {
        // cout << "notnull" << endl;
        // return vec3(1.0, 0.0, 0.0);
        vec3 normal;
        vec3 intP = vec3(closest.target->_transform * vec4(closest.point, 1.0f));
        // closest.p.dir = vec3(output.target->_transform * vec4(ray.dir, 0.0f));
        // closest.p.ori = vec3(output.target->_transform * vec4(ray.ori, 1.0f));
        if (closest.target->_type == tri)
        {
            triangle *tri = (triangle *)closest.target;
            normal = tri->findNormal();
        }else{
            sphere *sph = (sphere *)closest.target;
            normal = sph->findNormal(closest.point); //need 
        }
        normal = normalize(vec3(inverse(transpose(closest.target->_transform)) * vec4(normal, 0.0f)));
        for (int i = 0; i < numused; i++)
        {
            vec3 eyedirn = normalize(closest.p.ori-intP); //???
            vec3 col;
            vec3 diffuse = closest.target->_diffuse;
            // cout<<diffuse[0]<<diffuse[1]<<diffuse[2]<<endl;
            vec3 specular = closest.target->_specular;
            float shininess = closest.target->_shininess;
            vec3 position;
            vec3 direction;
            vec4 lightDir;
            vec3 myhalf;
            vec3 color = vec3(lightcolor[3 * i], lightcolor[3 * i + 1], lightcolor[3 * i + 2]);
            direction = vec3(lightposn[4 * i], lightposn[4 * i + 1], lightposn[4 * i + 2]);
            lightDir = vec4(lightposn[4 * i], lightposn[4 * i + 1], lightposn[4 * i + 2], lightposn[4 * i + 3]);
            //if under shadow with this light, go next 
            if (computeV(intP, lightDir) == 0) {
                continue;
            }
            if (lightposn[4 * i + 3] == 0)
            { // directional
                direction = normalize(direction);
                myhalf = normalize(direction + eyedirn);
                col = ComputeLight(direction, color, normal, myhalf, diffuse, specular, shininess);
            }
            else
            { // point???
                position = vec3(lightposn[4 * i], lightposn[4 * i + 1], lightposn[4 * i + 2]) / lightposn[4 * i + 3];
                direction = normalize(position - intP);
                myhalf = normalize(direction + eyedirn);
                float dist = distance(closest.point, position);
                col = ComputeLight(direction, color, normal, myhalf, diffuse, specular, shininess) / (attenuation[0] + attenuation[1] * dist + attenuation[2] * powf(dist, 2));
            }
            finalcolor = finalcolor + col;
        }
        // cout<<finalcolor[0]<<finalcolor[1]<<finalcolor[2]<<endl;
        finalcolor = finalcolor + closest.target->_ambient + closest.target->_emission;
        // cout << finalcolor[0] << " " << finalcolor[1] << " " << finalcolor[2] << endl;

        return finalcolor;
    }
}



int main(int argc, char *argv[])
{

    // uwv

    // Render
    // cout<<argv[1]<<endl;

    // cout<<(triangle)obj[0]<<endl;
    /*glm::mat4 camera;
    camera[0] = glm::vec4(1, 0, 0, 1);
    camera[1] = glm::vec4(0, 1, 0, 0);
    camera[2] = glm::vec4(0, 1, 1, 0);
    camera[3] = glm::vec4(0, 0, 1 ,0);
    vec4 v4 = vec4(1,2,3,4);
    vec4 result = camera * v4;
    float x = result[0];
    float y = result[1];
    float z = result[2];
    float w = result[3];*/

    readfile(argv[1]);
    // cout<< lightcolor[0] <<lightcolor[1]<<lightcolor[2]<<endl;
    // cout << lightposn[0] << lightposn[1] << lightposn[2] << endl;

    std::cout << "P3\n"
              << image_width << ' ' << image_height << "\n255\n";
    // cout<<obj[1]->_type<<endl;
    for (int i = 0; i < image_height; ++i)
    {
        for (int j = 0; j < image_width; ++j)
        {
            Ray ray(i+0.5, j+0.5);
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
