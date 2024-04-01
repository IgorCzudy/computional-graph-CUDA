#include <gtest/gtest.h>
#include "../src/vector.hpp"


TEST(SquareRootTest, PositiveNos) { 
    std::vector<float> elements = {2.0};//, 2.0, 3.0};
    Vector vec1(elements, "vec1");
    
    std::vector<float> elements2 = {4.0};//, 5.0, 6.0};
    Vector vec2(elements2, "vec2");

    Vector vec3 = vec1 * vec2;
    vec3.backword();

    ASSERT_EQ(4, vec1.grads[0]);
    ASSERT_EQ(2, vec2.grads[0]);
    ASSERT_EQ(1, vec3.grads[0]);
}


TEST(AdditionTest, PositiveNos) { 
    std::vector<float> elements = {2.0};//, 2.0, 3.0};
    Vector vec1(elements, "vec1");
    std::vector<float> elements2 = {4.0};//, 5.0, 6.0};
    Vector vec2(elements2, "vec2");
    Vector vec3 = vec1 + vec2;
    vec3.backword();

    ASSERT_EQ(1, vec1.grads[0]);
    ASSERT_EQ(1, vec2.grads[0]);
    ASSERT_EQ(1, vec3.grads[0]);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}