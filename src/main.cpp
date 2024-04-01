#include <iostream>
#include "vector.hpp"

int main() {
    std::vector<float> elements = {2.0};//, 2.0, 3.0};
    Vector vec1(elements, "vec1");
    
    std::vector<float> elements2 = {4.0};//, 5.0, 6.0};
    Vector vec2(elements2, "vec2");

    Vector vec3 = vec1 * vec2;

    // vec1._backword();
    vec3.backword();
    
    // std::vector<float> elements4 = {3.0};//, 2.0, 3.0};
    // Vector vec4(elements4, "vec4");
    // vec4._backword();
    // Vector vec5 = vec3 * vec4; 
    // std::cout << vec5.values[0] << std::endl;
    // vec4.backword();


    // std::cout <<"vec1: "<<vec1.grads[0]<<" "<< vec1.grads[1]<<" "<< vec1.grads[2] << std::endl; 
    // std::cout <<"vec2: "<<vec2.grads[0]<<" "<< vec2.grads[1]<<" "<< vec2.grads[2] << std::endl; 
    // std::cout <<"vec3: "<<vec3.grads[0]<<" "<< vec3.grads[1]<<" "<< vec3.grads[2] << std::endl; 

    return 0;
}