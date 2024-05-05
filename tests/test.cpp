#include <gtest/gtest.h>
#include "../src/vector.hpp"

struct NewtorchTest : public testing::Test {
    void SetUp() override{
        vec1 = Vector({2.0, 3.0, 4.0}, "vec1");
        vec2 = Vector({4.0, 5.0, 6.0}, "vec2");
    }

    void compare_vectors(std::vector<float> v, std::vector<float> expected){
        ASSERT_EQ(v.size(), expected.size()) << "Vectors x and y are of unequal length";

        for (int i = 0; i < v.size(); ++i) {
            EXPECT_EQ(v[i], expected[i]) << "Vectors x and y differ at index " << i;
        }

    }
    
    Vector vec1;
    Vector vec2;
};

TEST_F(NewtorchTest, AdditionTest) {
    Vector vec3 = vec1 + vec2;
    vec3.backword();

    compare_vectors(vec1.grads, {1, 1, 1});
    compare_vectors(vec2.grads, {1, 1, 1});
    compare_vectors(vec3.grads, {1, 1, 1});
    compare_vectors(vec3.values, {6, 8, 10});
}

TEST_F(NewtorchTest, ThreeNumbersAdditionTest){
    Vector vec3({1.0, 2.0, 3.0}, "vec3");
    Vector vec4 = vec1 + vec2 + vec4;
    vec4.backword();

    compare_vectors(vec1.grads, {1, 1, 1});
    compare_vectors(vec2.grads, {1, 1, 1});
    compare_vectors(vec3.grads, {1, 1, 1});
    compare_vectors(vec4.grads, {1, 1, 1});
    compare_vectors(vec4.values, {7, 10, 13});
}
    

TEST_F(NewtorchTest, MultiplicationTest) { 
    Vector vec3 = vec1 * vec2;
    vec3.backword();

    compare_vectors(vec1.grads, {4, 5, 6});
    compare_vectors(vec2.grads, {2, 3, 4});
    compare_vectors(vec3.grads, {1, 1, 1});
    compare_vectors(vec3.values, {8, 15, 24});
}

TEST_F(NewtorchTest, MultiplicationByFloatTest){
    Vector vec3 = vec1 * 2;
    vec3.backword();

    compare_vectors(vec1.grads, {2, 2, 2});
    compare_vectors(vec3.grads, {1, 1, 1});
    compare_vectors(vec3.values, {4, 6, 8});

}

TEST_F(NewtorchTest, PowerTest) { 
    Vector vec3 = vec1 ^ 3;
    vec3.backword();

    compare_vectors(vec1.grads, {12, 27, 48}); //3 * vec1 * vec1
    compare_vectors(vec3.grads, {1, 1, 1});
    compare_vectors(vec3.values, {8, 27, 64});
}

TEST_F(NewtorchTest, NegationTest){
    Vector vec3 = -vec1;
    vec3.backword();

    compare_vectors(vec1.grads, {-1, -1, -1});
    compare_vectors(vec3.grads, {1, 1, 1});
    compare_vectors(vec3.values, {-2, -3, -4});

}

TEST_F(NewtorchTest, DivisionTest) { 
    Vector vec3 = vec1 / vec2;
    vec3.backword();

    compare_vectors(vec1.grads, (vec2^(-1)).values);
    compare_vectors(vec2.grads, (-vec2 * vec1).values);
    compare_vectors(vec3.grads, {1, 1, 1});
    compare_vectors(vec3.values, {0.5, 3/5, 4/6});
}

TEST_F(NewtorchTest, SubtractionTest) { 
    Vector vec3 = vec1 - vec2;
    vec3.backword();

    compare_vectors(vec1.grads, {1, 1, 1});
    compare_vectors(vec2.grads, {-1, -1, -1});
    compare_vectors(vec3.grads, {1, 1, 1});
    compare_vectors(vec3.values, {-2, -2, -2});
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}