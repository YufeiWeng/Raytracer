

#include "object.h"

#ifdef MAINPROGRAM 
#define EXTERN 
#else 
#define EXTERN extern 
#endif

EXTERN int image_width; //from test scene 
EXTERN int image_height;
EXTERN float fovy;
EXTERN vec3 eye; // 0 for now
EXTERN vec3 center;
EXTERN vec3 up;



EXTERN vector<object> obj;

EXTERN float ambient[3];
EXTERN float diffuse[3];
EXTERN float specular[3];
EXTERN float emission[3];
EXTERN float shininess;
const vec3 A(2.0, 4.0, 1.0);
const vec3 B(0.0, 0.0, 1.0);
const vec3 C(0.0, -1.0, 3.0);


