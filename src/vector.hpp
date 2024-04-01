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
    Vector(std::vector<float> values_int, std::string label_int);
    Vector operator+(Vector& other);
    Vector operator*(Vector& other);
    void backword();
    // void setName(std::string n);
    // void setAge(int a);
    // void displayInfo();
};

#endif