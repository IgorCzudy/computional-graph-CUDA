#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <memory>
#include <set>
#include <stack>
#include <tuple>



class Vector : public std::enable_shared_from_this<Vector>{
private:
    std::string op;
    std::string label;
    std::function<void()> _backword;

    // void build_topo(std::set<Vector*>& visited, std::stack<Vector*>& topo);

public:
    std::tuple<std::shared_ptr<Vector>, std::shared_ptr<Vector>> prev;
    std::vector<float> values;
    std::vector<float> grads;


public:
    Vector() {}  // Default constructor for initialization
    Vector(std::vector<float> values_int, std::string label_int);
    
    Vector operator+(Vector& other){throw "Not implemented";};;
    std::shared_ptr<Vector> operator*(std::shared_ptr<Vector> other);
    Vector operator*(float other){throw "Not implemented";};;
    Vector operator^(float power){throw "Not implemented";};;
    Vector operator-() {return *this * -1;};
    Vector operator-(Vector& other){throw "Not implemented";}; //{return *this + (-other);};
    Vector operator/(Vector& other){throw "Not implemented";}; // {return *this * (other ^ -1);};
    ~Vector() {std::cout << "Destructor called for " << label << std::endl;}

    void backword();
    // void setName(std::string n);
    // void setAge(int a);
    // void displayInfo();
};

inline std::shared_ptr<Vector> operator*(const std::shared_ptr<Vector>& lhs, const std::shared_ptr<Vector>& rhs) {
    return (*lhs) * rhs;
}

#endif //  VECTOR_HPP