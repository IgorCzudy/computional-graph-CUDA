#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include <vector>
#include <functional>
#include <iostream>

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
    Vector operator*(float other);
    Vector operator^(float power);
    Vector operator-() {return *this * -1;};
    Vector operator-(Vector& other){throw "Not implemented";}; //{return *this + (-other);};
    Vector operator/(Vector& other){throw "Not implemented";}; // {return *this * (other ^ -1);};
    ~Vector() {std::cout << "Destructor called for " << label << std::endl;}

    void backword();
    // void setName(std::string n);
    // void setAge(int a);
    // void displayInfo();
};

#endif