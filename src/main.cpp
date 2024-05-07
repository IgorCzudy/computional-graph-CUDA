#include <iostream>
#include "vector.hpp"
#include <memory>


int main() {
    try{
        std::shared_ptr<Vector> vector1 = create_vector({2.0}, "vec1");
        std::shared_ptr<Vector> vector2 = create_vector({4.0}, "vec2");
        std::shared_ptr<Vector> vector3 = create_vector({-1.0}, "vec3");

        std::shared_ptr<Vector> vector4 = vector1 + vector2 * vector3 ;
        
        vector4->backward();
        std::cout << vector1 << std::endl;
        std::cout << vector2 << std::endl;
        std::cout << vector3 << std::endl;
        std::cout << vector4 << std::endl;

    }
    catch(const char* msg){
        std::cout << "ERROR: " << msg << std::endl;
    }

    return 0;
}