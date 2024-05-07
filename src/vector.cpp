#include "vector.hpp"
#include <cmath>

// ADDITIONAL OPERATORS FOR STD::VECTOR

std::vector<float> operator+(const std::vector<float>& vec1, const std::vector<float>& vec2){
    if (vec1.size() == vec2.size()){
        std::vector<float> out = std::vector<float>(vec1.size(), 0);

        for (int i=0; i<out.size(); i++){
            out[i] = vec1[i] + vec2[i];
        }
        return out;
    }

    if (vec1.size() == 1 && vec2.size() > 1){
        std::vector<float> broadcasted = std::vector<float>(vec2.size(), vec1[0]);
        return broadcasted + vec2;
    }

    if (vec2.size() == 1 && vec1.size() > 1){
        std::vector<float> broadcasted = std::vector<float>(vec1.size(), vec2[0]);
        return broadcasted + vec1;
    }

    throw "Vectors must have the same size or one must be size 1 in order to add them";
    return std::vector<float>(0);
}


std::vector<float> operator*(std::vector<float> vec1, std::vector<float> vec2){
    if (vec1.size() == vec2.size()){
        std::vector<float> out = std::vector<float>(vec1.size(), 0);

        for (int i=0; i<out.size(); i++){
            out[i] = vec1[i] * vec2[i];
        }
        return out;
    }

    if (vec1.size() == 1 && vec2.size() > 1){
        std::vector<float> broadcasted = std::vector<float>(vec2.size(), vec1[0]);
        return broadcasted * vec2;
    }

    if (vec2.size() == 1 && vec1.size() > 1){
        std::vector<float> broadcasted = std::vector<float>(vec1.size(), vec2[0]);
        return broadcasted * vec1;
    }

    throw "Vectors must have the same size or one must be size 1 in order to multiply them";
    return std::vector<float>(0);

}


std::vector<float> operator*(float number, std::vector<float> vec1){
    return std::vector<float>(vec1.size(), number) * vec1;
}


std::vector<float> operator^(std::vector<float> vec, float power){
    std::vector<float> out = std::vector<float>(vec.size(), 0);
    for (int i=0; i<out.size(); i++){
        out[i] = std::pow(vec[i], power);
    }
    return out;
}

// BASICS FOR VECTOR CLASS

Vector::Vector(std::vector<float> values_int, std::string label_int){
    values = std::move(values_int);
    grads = std::vector<float>(values.size(), 0);
    _backward = [](){}; //empty lambda expression 
    prev = std::tuple<std::shared_ptr<Vector>, std::shared_ptr<Vector>>(nullptr, nullptr);
    op = "";
    label = label_int;  
}

std::ostream& operator<< (std::ostream& stream, const std::shared_ptr<Vector> vector){
    stream << vector->get_label() << " = [values[";
    for (int i=0; i<vector->get_values().size(); i++){
        stream << vector->get_values()[i];
        if (i != vector->get_values().size()-1){
            stream << ", ";
        }
    }
    stream << "]";
    stream << "  grads[";
    for (int i=0; i<vector->get_grads().size(); i++){
        stream << vector->get_grads()[i];
        if (i != vector->get_grads().size()-1){
            stream << ", ";
        }
    }
    stream << "]]";
    return stream;
}

void Vector::zero_lambda(Vector* v, std::set<Vector*> visited){
    if (visited.find(v) == visited.end()){
        visited.insert(v);
        v -> _backward = [](){}; //empty lambda expression to avoid memory leak
        std::apply([&](std::shared_ptr<Vector> child1, std::shared_ptr<Vector> child2) {
            if (child1 != nullptr) zero_lambda(child1.get(), visited);
            if (child2 != nullptr) zero_lambda(child2.get(), visited);
        }, v->prev);
    }
}

Vector::~Vector(){
    // std::cout << "Destructor called for " << label << std::endl;
    std::set<Vector*> visited;
    zero_lambda(this, visited);
}

// OPERATORS FOR VECTOR CLASS

std::shared_ptr<Vector> Vector::operator+(std::shared_ptr<Vector> other) {
    std::vector<float> out_values = this->values + other->values;

    std::shared_ptr<Vector> out = std::make_shared<Vector>(out_values,  this->label + "+" + other->label);
    out->prev = std::tuple<std::shared_ptr<Vector>, std::shared_ptr<Vector>>(shared_from_this(), other);
    out->op = "+";

    out->_backward = [this, other, &out](){
        this->grads = this->grads + (1.0 * out->grads);
        other->grads = other->grads + (1.0 * out->grads);
    };
    return out;
}

std::shared_ptr<Vector> Vector::operator*(std::shared_ptr<Vector> other){
    
    std::vector<float> out_values = this->values * other->values;

    std::shared_ptr<Vector> out = std::make_shared<Vector>(out_values,  this->label + "*" + other->label);
    out->prev = std::tuple<std::shared_ptr<Vector>, std::shared_ptr<Vector>>(shared_from_this(), other);
    out->op = "*";

    out->_backward = [this, other, &out](){
        this->grads = this->grads + (other->values * out->grads);
        other->grads = other->grads + (this->values * out->grads);
    };
    
    return out;
}

std::shared_ptr<Vector> Vector::operator*(float other){
    std::vector<float> out_values = other * this->values;

    std::shared_ptr<Vector> out = std::make_shared<Vector>(out_values,  this->label + "*" + std::to_string(other));
    out->prev = std::tuple<std::shared_ptr<Vector> , std::shared_ptr<Vector>>(shared_from_this(), nullptr);
    out->op = "*";

    out->_backward = [this, other, out](){ // we have memory leak here because of out and not &out
        this->grads = this->grads + (other * out->grads);
    };
    
    return out;
}

std::shared_ptr<Vector> Vector::operator^(float power){
    std::vector<float> out_values = this->values ^ power;

    std::shared_ptr<Vector> out = std::make_shared<Vector>(out_values, this->label + "^" + std::to_string(power));
    out->prev = std::tuple<std::shared_ptr<Vector>, std::shared_ptr<Vector>>(shared_from_this(), nullptr);
    out->op = "^";

    out->_backward = [this, power, out](){ // we have memory leak here because of out and not &out
        this->grads = this->grads + (power * (this->values ^ (power-1)) * out->grads);
    };

    return out;
}

std::shared_ptr<Vector> Vector::operator-(){return shared_from_this() * -1.0;};

std::shared_ptr<Vector> Vector::operator-(std::shared_ptr<Vector> other){return shared_from_this() + -other;};
std::shared_ptr<Vector> Vector::operator/(std::shared_ptr<Vector> other){return shared_from_this() * (other ^ (-1));};


// BACKWARD PROPAGATION

void Vector::build_topo(std::shared_ptr<Vector> v, std::set<std::shared_ptr<Vector>>& visited, std::stack<std::shared_ptr<Vector>>& topo){
    if (visited.find(v) == visited.end()){
        visited.insert(v);
        std::apply([&](std::shared_ptr<Vector> child1, std::shared_ptr<Vector> child2) {
            if (child1 != nullptr) build_topo(child1, visited, topo);
            if (child2 != nullptr) build_topo(child2, visited, topo);
        }, v->prev);
        topo.push(v);
    }
}


void Vector::backward(){
    std::stack<std::shared_ptr<Vector>> topo;
    std::set<std::shared_ptr<Vector>> visited;

    build_topo(shared_from_this(), visited, topo);
    
    this->grads = std::vector<float>(this->grads.size(), 1);

    while (topo.empty() == false) {
        topo.top()->_backward();
        topo.pop();
    }
}