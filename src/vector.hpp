#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include <vector>
#include <functional>

class Vector{
private:
    std::string op;
    std::string label;
public:
    std::vector<float> values;
    std::vector<float> grads;
    std::tuple<Vector*, Vector*> prev;
    std::function<void()> _backword;


public:
    Vector() {}  // Default constructor for initialization
    Vector(std::vector<float> values_int, std::string label_int);
    Vector operator+(Vector& other);
    Vector operator*(Vector& other);
    Vector operator*(float other) {throw("Not implemented"); return *this;} // Not implemented;
    Vector operator-(Vector& other) {throw ("Not implemented"); return *this;};
    Vector operator-() {throw ("Not implemented"); return *this;};
    Vector operator/(Vector& other) {throw ("Not implemented"); return *this;};
    Vector operator^(float power) {throw ("Not implemented"); return *this;};

    void backword();
    // void setName(std::string n);
    // void setAge(int a);
    // void displayInfo();
};

#endif