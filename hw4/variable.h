#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
typedef glm::vec3 vec3;

#ifdef MAINPROGRAM 
#define EXTERN 
#else 
#define EXTERN extern 
#endif

const int image_width = 640; //from test scene 
const int image_height = 480;
const float fovy(45);
const float fovx = fovy * (image_width / (image_height *1.0));
const vec3 eye(-4, -4, 4); //0 for now 
const vec3 center(0.0, 1.0, 0.0);

const vec3 up(1.0, 0.0, 0.0);
const vec3 A(2.0, 4.0, 1.0);
const vec3 B(0.0, 0.0, 1.0);
const vec3 C(0.0, -1.0, 3.0);  

