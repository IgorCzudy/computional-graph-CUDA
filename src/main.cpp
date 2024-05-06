#include <iostream>
#include "vector.hpp"
#include <memory>


int main() {
    try{
        std::shared_ptr<Vector> vector1 = std::make_shared<Vector>(std::vector<float>{2.0}, "vec1");
        std::shared_ptr<Vector> vector2 = std::make_shared<Vector>(std::vector<float>{4.0}, "vec2");
        std::shared_ptr<Vector> vector3 = std::make_shared<Vector>(std::vector<float>{-1.0}, "vec3");

        std::shared_ptr<Vector> vector4 = vector2 / vector1;
        
        std::cout << "result " << vector4->values[0] << std::endl;
        vector4->backword();
        std::cout << "grad1 " << vector1->grads[0] << std::endl;
        std::cout << "grad2 " << vector2->grads[0] << std::endl;
        std::cout << "grad3 " << vector3->grads[0] << std::endl;
        std::cout << "grad result " << vector4->grads[0] << std::endl;
    }
    catch(const char* msg){
        std::cout << "ERROR: " << msg << std::endl;
    }

    return 0;
}