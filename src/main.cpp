#include <iostream>
#include "vector.hpp"

int main() {
    try{
        Vector vec1({2.0}, "vec1");
        Vector vec2({4.0}, "vec2");

        Vector vec4({3.0}, "vec4");
        // std::cout << (vec1 * vec2 * vec4).values[0] << std::endl;
        // Vector vec5 = vec1 * vec2 * vec4;
        // std::cout << vec5.values[0] << std::endl;
        // vec5.backword();
        // std::cout << vec1.grads[0] << std::endl;
        
        Vector vec8 = -vec1;
        vec8.backword();
        std::cout << vec8.values[0] << std::endl;
        std::cout << vec1.grads[0] << std::endl;

        // Vector vec3 = vec1 * vec2; //8
        // vec3.backword();
        
        // Vector vec5 = vec3 * vec4; //24
        // vec5.backword();

        // Vector vec6 = vec5 * 2; //48
        // vec6.backword();

        // Vector vec7 = vec6 ^ 3; 
        // vec7.backword();
    }
    catch(const char* msg){
        std::cout << "ERROR: " << msg << std::endl;
    }


    // std::cout <<"vec1: "<<vec1.grads[0]<<" "<< vec1.grads[1]<<" "<< vec1.grads[2] << std::endl; 
    // std::cout <<"vec2: "<<vec2.grads[0]<<" "<< vec2.grads[1]<<" "<< vec2.grads[2] << std::endl; 
    // std::cout <<"vec3: "<<vec3.grads[0]<<" "<< vec3.grads[1]<<" "<< vec3.grads[2] << std::endl; 

    return 0;
}