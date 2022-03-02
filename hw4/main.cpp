#include "main.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>  //If there are redlines, go and check: https://www.google.com/search?q=how+to+include+glm+in+visual+studio+2019&ei=tbkeYuH6BZrHkPIPgMex2A0&ved=0ahUKEwihqa6plab2AhWaI0QIHYBjDNsQ4dUDCA4&uact=5&oq=how+to+include+glm+in+visual+studio+2019&gs_lcp=Cgdnd3Mtd2l6EAMyBQghEKsCOgcIABBHELADOgYIABAWEB46BQgAEIYDOgUIIRCgAUoECEEYAEoECEYYAFCyBVj-C2D3DmgBcAF4AYAB9AGIAYcGkgEFMC40LjGYAQCgAQHIAQjAAQE&sclient=gws-wiz#kpvalbx=_u7keYvz9FrefkPIPt8SO8Aw20
using namespace std;

int main() {

    // Image

    const int image_width = 256;
    const int image_height = 256;

    // Camera

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            auto r = double(i) / (image_width - 1);
            auto g = double(j) / (image_height - 1);
            auto b = 0.25;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
}
