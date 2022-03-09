
#include "variable.h"
#include "readfile.h"
#include "transform.h"
// default value t for every object
// float INF = 35415; //for test
void rightmultiply(const mat4 &M, stack<mat4> &transfstack)
{
    mat4 &T = transfstack.top();
    T = T * M;
}
bool readvals(stringstream &s, const int numvals, float *values)
{
    for (int i = 0; i < numvals; i++)
    {
        s >> values[i];
        if (s.fail())
        {
            cout << "Failed reading value " << i << " will skip\n";
            return false;
        }
    }
    return true;
}

void readfile(const char *filename)
{
    ambient[0] = 0.2;ambient[1] = 0.2;ambient[2] = 0.2;
    diffuse[0] = 0.0;diffuse[1] = 0.0;diffuse[2] = 0.0;
    specular[0] = 0.0;specular[1] = 0.0;specular[2] = 0.0;
    emission[0] = 0.0;emission[1] = 0.0;emission[2] = 0.0;
    shininess = 0.0;

    string str, cmd;
    ifstream in;
    int i;
    vector<vec3> vertexes;
    numused=0;
    in.open(filename);
    if (in.is_open())
    {
        stack<mat4> transfstack;
        transfstack.push(mat4(1.0)); // identity

        getline(in, str);
        while (in)
        {
            if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#'))
            {
                // Ruled out comment and blank lines
                stringstream s(str);
                float values[10];
                bool validinput;

                s >> cmd;
                if (cmd == "size")
                {
                    validinput = readvals(s, 2, values);
                    if (validinput)
                    {
                        image_width = (int)values[0];
                        image_height = (int)values[1];
                    }
                }
                else if (cmd == "camera")
                {
                    validinput = readvals(s, 10, values); // 10 values eye cen up fov
                    if (validinput)
                    {

                        // YOUR CODE FOR HW 2 HERE
                        // Use all of values[0...9]
                        // You may need to use the upvector fn in Transform.cpp
                        // to set up correctly.
                        // Set eyeinit upinit center fovy in variables.h
                        fovy = values[9];

                        up.z = values[8];
                        up.y = values[7];
                        up.x = values[6];
                        center.z = values[5];
                        center.y = values[4];
                        center.x = values[3];
                        eye.z = values[2];
                        eye.y = values[1];
                        eye.x = values[0];
                    }
                }
                else if (cmd == "ambient")
                {
                    validinput = readvals(s, 3, values); // colors
                    if (validinput)
                    {
                        for (i = 0; i < 3; i++)
                        {
                            ambient[i] = values[i];
                        }
                    }
                }
                else if (cmd == "diffuse")
                {
                    validinput = readvals(s, 3, values);
                    if (validinput)
                    {
                        for (i = 0; i < 3; i++)
                        {
                            diffuse[i] = values[i];
                        }
                    }
                }
                else if (cmd == "specular")
                {
                    validinput = readvals(s, 3, values);
                    if (validinput)
                    {
                        for (i = 0; i < 3; i++)
                        {
                            specular[i] = values[i];
                        }
                    }
                }
                else if (cmd == "emission")
                {
                    validinput = readvals(s, 3, values);
                    if (validinput)
                    {
                        for (i = 0; i < 3; i++)
                        {
                            emission[i] = values[i];
                        }
                    }
                }
                else if (cmd == "shininess")
                {
                    validinput = readvals(s, 1, values);
                    if (validinput)
                    {
                        shininess = values[0];
                    }
                }
                else if (cmd == "vertex")
                {
                    validinput = readvals(s, 3, values);

                    if (validinput)
                    {
                        vertexes.push_back(vec3(values[0], values[1], values[2]));
                    }
                }
                else if (cmd == "point")
                {
                    if (numused == numLights)
                    { // No more Lights
                        cerr << "Reached Maximum Number of Lights " << numused << " Will ignore further lights\n";
                    }
                    else
                    {
                        validinput = readvals(s, 6, values); // Position/color for lts.
                        if (validinput)
                        {

                            for (int i = 0; i < 3; i++)
                            {
                                lightposn[i + numused * 4] = values[i];
                            }
                            lightposn[3 + numused * 4] = 1;
                            for (int j = 0; j < 3; j++)
                            {
                                lightcolor[j + numused * 3] = values[j + 3];
                            }
                            ++numused;
                        }
                    }
                }
                else if (cmd == "directional")
                {
                    if (numused == numLights)
                    { // No more Lights
                        cerr << "Reached Maximum Number of Lights " << numused << " Will ignore further lights\n";
                    }
                    else
                    {
                        validinput = readvals(s, 6, values); // Position/color for lts.
                        if (validinput)
                        {
                            
                            for (int i = 0; i < 3; i++)
                            {
                                lightposn[i + numused * 4] = values[i];

                            }
                            lightposn[3 + numused * 4] = 0;
                            for (int j = 0; j < 3; j++)
                            {
                                lightcolor[j + numused * 3] = values[j + 3];

                            }
                            ++numused;
                        }
                    }
                }
                else if (cmd == "tri")
                {
                    validinput = readvals(s, 3, values);
                    if (validinput)
                    {

                        obj.push_back(new triangle(tri, ambient, diffuse, specular, emission, shininess, transfstack.top(),
                                                   vertexes[values[2]], vertexes[values[1]], vertexes[values[0]]));
                    }
                }
                else if (cmd == "sphere")
                {
                    validinput = readvals(s, 4, values);
                    if (validinput)
                    {
                        obj.push_back(new sphere(sph, ambient, diffuse, specular, emission, shininess, transfstack.top(),
                                                 vec3(values[0], values[1], values[2]), values[3]));
                    }
                }
                else if (cmd == "translate"){
                    validinput = readvals(s, 3, values);
                    if (validinput)
                    {
                        mat4 tr = Transform::translate(values[0], values[1], values[2]);
                        rightmultiply(tr, transfstack);
                    }
                }else if (cmd == "scale"){
                    validinput = readvals(s, 3, values);
                    if (validinput)
                    {

                        mat4 sc = Transform::scale(values[0], values[1], values[2]);

                        rightmultiply(sc, transfstack);
                    }
                }
                else if (cmd == "rotate")
                {
                    validinput = readvals(s, 4, values);
                    if (validinput)
                    {
                        mat4 ro = mat4(Transform::rotate(values[3], vec3(values[0], values[1], values[2])));
                        rightmultiply(ro, transfstack);
                    }
                }
                else if (cmd == "pushTransform")
                {
                    transfstack.push(transfstack.top());
                }
                else if (cmd == "popTransform")
                {
                    if (transfstack.size() <= 1)
                    {
                        cerr << "Stack has no elements.  Cannot Pop\n";
                    }
                    else
                    {
                        transfstack.pop();
                    }
                }
            }

            // cout << str << endl;
            getline(in, str);
        }
    }
    else
    {
        cerr << "Unable to Open Input Data File " << filename << "\n";
        throw 2;
    }
}