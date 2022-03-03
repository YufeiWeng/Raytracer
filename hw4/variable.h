#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
typedef glm::vec3 vec3;

#ifdef MAINPROGRAM 
#define EXTERN 
#else 
#define EXTERN extern 
#endif

extern int image_width = 640; //from test scene 
extern int image_height = 480;
extern float fovy(45);
extern float fovx = fovy * (image_width / (image_height *1.0));
extern vec3 eye(-4, -4, 4); //0 for now 
extern vec3 center(0.0, 1.0, 0.0);

extern vec3 up(1.0, 0.0, 0.0);
extern vec3 A(2.0, 4.0, 1.0);
extern vec3 B(0.0, 0.0, 1.0);
extern vec3 C(0.0, -1.0, 3.0);


