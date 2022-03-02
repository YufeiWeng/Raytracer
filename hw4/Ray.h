
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace std;

class Ray {
public:
    glm::vec3 ori;
    glm::vec3 dir;
public:
    glm::vec3 at(double t) const;
    Ray(const glm::vec3 origin, const glm::vec3 direction);
};


