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
    std::function<void()> _backward;
    std::vector<float> values;
    std::vector<float> grads;

    static void build_topo(std::shared_ptr<Vector> v, std::set<std::shared_ptr<Vector>>& visited, std::stack<std::shared_ptr<Vector>>& topo);
    static void zero_lambda(Vector* v, std::set<Vector*> visited);
    std::tuple<std::shared_ptr<Vector>, std::shared_ptr<Vector>> prev;

public:
    Vector(std::vector<float> values_int, std::string label_int);
    
    std::vector<float> get_values(){return values;}
    std::vector<float> get_grads(){return grads;}
    std::string get_label(){return label;}
    
    void backward();

    std::shared_ptr<Vector> operator+(std::shared_ptr<Vector> other);
    std::shared_ptr<Vector> operator*(std::shared_ptr<Vector> other);
    std::shared_ptr<Vector> operator*(float other);
    std::shared_ptr<Vector> operator^(float power);
    std::shared_ptr<Vector> operator-();
    std::shared_ptr<Vector> operator-(std::shared_ptr<Vector> other);
    std::shared_ptr<Vector> operator/(std::shared_ptr<Vector> other);

    ~Vector();
};


std::ostream& operator<< (std::ostream& stream, const std::shared_ptr<Vector> vector);

inline std::shared_ptr<Vector> create_vector(std::vector<float> values, std::string label)
{
    return std::make_shared<Vector>(values, label);

}

// OPERATORS

inline std::shared_ptr<Vector> operator*(const std::shared_ptr<Vector>& lhs, const std::shared_ptr<Vector>& rhs) {
    return (*lhs) * rhs;
}

inline std::shared_ptr<Vector> operator+(const std::shared_ptr<Vector>& lhs, const std::shared_ptr<Vector>& rhs) {
    return (*lhs) + rhs;
}

inline std::shared_ptr<Vector> operator*(const std::shared_ptr<Vector>& lhs, const float rhs) {
    return (*lhs) * rhs;
}

inline std::shared_ptr<Vector> operator^(const std::shared_ptr<Vector>& lhs, const float power) {
    return (*lhs) ^ power;
}

inline std::shared_ptr<Vector> operator-(const std::shared_ptr<Vector>& num) {
    return -(*num);
}

inline std::shared_ptr<Vector> operator-(const std::shared_ptr<Vector>& lhs, const std::shared_ptr<Vector>& rhs) {
    return (*lhs) - rhs;
}

inline std::shared_ptr<Vector> operator/(const std::shared_ptr<Vector>& lhs, const std::shared_ptr<Vector>& rhs) {
    return (*lhs) / rhs;
}


#endif //  VECTOR_HPP