
#include "variable.h"
#include "readfile.h"

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
    ambient[0]=0.0; ambient[1]=0.0; ambient[2]=0.0;
    diffuse[0]=0.0; diffuse[1]=0.0; diffuse[2]=0.0;
    specular[0]=0.0; specular[1]=0.0; specular[2]=0.0;
    emission[0]=0.0; emission[1]=0.0; emission[2]=0.0;
    shininess=0.0;

    string str, cmd;
    ifstream in;
    int i;
    vector<vec3> vertexes;

    in.open(filename);
    if (in.is_open())
    {
        getline(in, str);
        while (in)
        {
            if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#'))
            {
                // Ruled out comment and blank lines
                stringstream s(str);
                float values[10];
                bool validinput;
                s >>cmd;
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
                    validinput = readvals(s,3,values);

                    if(validinput)
                    {
                        vertexes.push_back(vec3(values[0],values[1],values[2]));

                    }
                }else if(cmd =="tri"){
                    validinput = readvals(s,3,values);
                    if (validinput)
                    {
                        
                        obj.push_back(new triangle(tri, ambient, diffuse, specular, emission, shininess,
                                               vertexes[values[0]], vertexes[values[1]], vertexes[values[2]]));
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