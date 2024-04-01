#include "vector.hpp"
#include <tuple>
#include <iostream>
#include <set>
#include <stack>


std::vector<float> operator+(const std::vector<float>& vec1, const std::vector<float>& vec2){
    std::vector<float> out = std::vector<float>(vec1.size(), 0);
    for (int i=0; i<out.size(); i++){
        out[i] = vec1[i] + vec2[i];
    }
    return out;
}


std::vector<float> operator*(std::vector<float> vec1, std::vector<float> vec2){
    std::vector<float> out = std::vector<float>(vec1.size(), 0);
    for (int i=0; i<out.size(); i++){
        out[i] = vec1[i] * vec2[i];
    }
    return out;
}


std::vector<float> operator*(float number, std::vector<float> vec1){
    return std::vector<float>(vec1.size(), number) * vec1;
}


Vector::Vector(std::vector<float> values_int, std::string label_int){
    values = values_int;
    grads = std::vector<float>(values.size(), 0);
    _backword = [](){}; //empty lambda expression 
    prev = std::tuple<Vector*, Vector*>(nullptr, nullptr);
    op = "";
    label = label_int;  
}


Vector Vector::operator+(Vector& other) {

    
    std::vector<float> out_values = this->values + other.values;

    Vector out = Vector(out_values, "out");
    out.prev = std::tuple<Vector*, Vector*>(this, &other);
    out.op = "+";

    out._backword = [&](){
        this->grads = this->grads + (1.0 * out.grads);
        other.grads = other.grads + (1.0 * out.grads);
    };
    return out;
}


Vector Vector::operator*(Vector& other){
    
    std::vector<float> out_values = this->values * other.values;

    Vector out = Vector(out_values, "out");
    out.prev = std::tuple<Vector*, Vector*>(this, &other);
    out.op = "*";

    out._backword = [&](){
        this->grads = this->grads + (other.values * out.grads);
        other.grads = other.grads + (this->values * out.grads);
    };
    
    return out;
}


void build_topo(Vector* v, std::set<Vector*>& visited, std::stack<Vector*>& topo){
    if (visited.find(v) == visited.end()){
        visited.insert(v);
        std::apply([&](Vector* child1, Vector* child2) {
            if (child1 != nullptr) build_topo(child1, visited, topo);
            if (child2 != nullptr) build_topo(child2, visited, topo);
        }, v->prev);
        topo.push(v);
    }
}


void Vector::backword(){
    std::stack<Vector*> topo;
    std::set<Vector*> visited;

    build_topo(this, visited, topo);
    
    this->grads = std::vector<float>(this->grads.size(), 1);
    while (topo.empty() == false) {
        topo.top()->_backword();
        topo.pop();
    }
}