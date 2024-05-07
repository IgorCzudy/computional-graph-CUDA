#include <gtest/gtest.h>
#include "../src/vector.hpp"

struct BasicOperationTest : public testing::Test {
    void SetUp() override{
        vec1 = std::make_shared<Vector>(std::vector<float>{2.0, 3.0, 4.0}, "vec1");
        vec2 = std::make_shared<Vector>(std::vector<float>{4.0, 5.0, 6.0}, "vec2");
    }

    void compare_vectors(std::vector<float> v, std::vector<float> expected, std::string name){
        ASSERT_EQ(v.size(), expected.size()) << name <<" are of unequal length";

        for (int i = 0; i < v.size(); ++i) {
            EXPECT_EQ(v[i], expected[i]) << name << " differ at index " << i;
        }

    }
    
    std::shared_ptr<Vector> vec1;
    std::shared_ptr<Vector> vec2;
};

TEST_F(BasicOperationTest, AdditionTest) {
    std::shared_ptr<Vector> vec3 = vec1 + vec2;
    vec3->backward();

    compare_vectors(vec1->get_grads(), {1, 1, 1}, "gradients of vec1");
    compare_vectors(vec2->get_grads(), {1, 1, 1}, "gradients of vec2");
    compare_vectors(vec3->get_grads(), {1, 1, 1}, "gradients of vec3");
    compare_vectors(vec3->get_values(), {6, 8, 10}, "results");
}

TEST_F(BasicOperationTest, ThreeNumbersAdditionTest){
    std::shared_ptr<Vector> vec3 = std::make_shared<Vector>(std::vector<float>{1.0, 2.0, 3.0}, "vec3");
    std::shared_ptr<Vector> vec4 = vec1 + vec2 + vec3;
    vec4->backward();

    compare_vectors(vec1->get_grads(), {1, 1, 1}, "gradients of vec1");
    compare_vectors(vec2->get_grads(), {1, 1, 1}, "gradients of vec2");
    compare_vectors(vec3->get_grads(), {1, 1, 1}, "gradients of vec3");
    compare_vectors(vec4->get_grads(), {1, 1, 1}, "gradients of vec4");
    compare_vectors(vec4->get_values(), {7, 10, 13}, "results");
}

TEST_F(BasicOperationTest, AdditionWithBroadcasting){
    std::shared_ptr<Vector> vec3 = create_vector({4.0}, "vec3");
    std::shared_ptr<Vector> vec4 = vec1 + vec3;
    vec4->backward();

    compare_vectors(vec1->get_grads(), {1, 1, 1}, "gradients of vec1");
    compare_vectors(vec3->get_grads(), {1, 1, 1}, "gradients of vec3");
    compare_vectors(vec4->get_grads(), {1, 1, 1}, "gradients of vec4");
    compare_vectors(vec4->get_values(), {6, 7, 8}, "results");
}

TEST_F(BasicOperationTest, MultiplicationTest) { 
    std::shared_ptr<Vector> vec3 = vec1 * vec2;
    vec3->backward();

    compare_vectors(vec1->get_grads(), {4, 5, 6}, "gradients of vec1");
    compare_vectors(vec2->get_grads(), {2, 3, 4}, "gradients of vec2");
    compare_vectors(vec3->get_grads(), {1, 1, 1}, "gradients of vec1");
    compare_vectors(vec3->get_values(), {8, 15, 24}, "results");
}

TEST_F(BasicOperationTest, ThreeNumbersMultiplicationTest){
    std::shared_ptr<Vector> vec3 = std::make_shared<Vector>(std::vector<float>{1.0, 2.0, 3.0}, "vec3");
    std::shared_ptr<Vector> vec4 = vec1 * vec2 * vec3;
    vec4->backward();

    compare_vectors(vec1->get_grads(), {4, 10, 18}, "gradients of vec1");
    compare_vectors(vec2->get_grads(), {2, 6, 12}, "gradients of vec2");
    compare_vectors(vec3->get_grads(), {8, 15, 24}, "gradients of vec3");
    compare_vectors(vec4->get_grads(), {1, 1, 1}, "gradients of vec4");
    compare_vectors(vec4->get_values(), {8, 30, 72}, "results");
}   

TEST_F(BasicOperationTest, MultiplicationWithBroadcasting){
    std::shared_ptr<Vector> vec3 = create_vector({2.0}, "vec3");
    std::shared_ptr<Vector> vec4 = vec1 * vec3;
    vec4->backward();

    compare_vectors(vec1->get_grads(), {2, 2, 2}, "gradients of vec1");
    compare_vectors(vec3->get_grads(), {2, 3, 4}, "gradients of vec3");
    compare_vectors(vec4->get_grads(), {1, 1, 1}, "gradients of vec4");
    compare_vectors(vec4->get_values(), {4, 6, 8}, "results");
}

TEST_F(BasicOperationTest, ThreeNumbersMultiplicationWithBroadcasting){
    std::shared_ptr<Vector> vec3 = std::make_shared<Vector>(std::vector<float>{2.0}, "vec3");
    std::shared_ptr<Vector> vec4 = vec1 * vec2 * vec3;
    vec4->backward();

    compare_vectors(vec1->get_grads(), {8, 10, 12}, "gradients of vec1");
    compare_vectors(vec2->get_grads(), {4, 6, 8}, "gradients of vec2");
    compare_vectors(vec3->get_grads(), {8, 15, 24}, "gradients of vec3");
    compare_vectors(vec4->get_grads(), {1, 1, 1}, "gradients of vec4");
    compare_vectors(vec4->get_values(), {16, 30, 48}, "results");
}

TEST_F(BasicOperationTest, MultiplicationByFloatTest){
    std::shared_ptr<Vector> vec3 = vec1 * 2;
    vec3->backward();

    compare_vectors(vec1->get_grads(), {2, 2, 2}, "gradients of vec1");
    compare_vectors(vec3->get_grads(), {1, 1, 1}, "gradients of vec3");
    compare_vectors(vec3->get_values(), {4, 6, 8}, "results");

}

TEST_F(BasicOperationTest, PowerTest) { 
    std::shared_ptr<Vector> vec3 = vec1 ^ 3;
    vec3->backward();

    compare_vectors(vec1->get_grads(), {12, 27, 48}, "gradients of vec1"); //3 * vec1 * vec1
    compare_vectors(vec3->get_grads(), {1, 1, 1}, "gradients of vec3");
    compare_vectors(vec3->get_values(), {8, 27, 64}, "results");
}

TEST_F(BasicOperationTest, NegationTest){
    std::shared_ptr<Vector> vec3 = -vec1;
    vec3->backward();

    compare_vectors(vec1->get_grads(), {-1, -1, -1}, "gradients of vec1");
    compare_vectors(vec3->get_grads(), {1, 1, 1}, "gradients of vec3");
    compare_vectors(vec3->get_values(), {-2, -3, -4}, "results");

}

TEST_F(BasicOperationTest, DivisionTest) { 
    std::shared_ptr<Vector> vec3 = vec1 / vec2;
    vec3->backward();

    compare_vectors(vec1->get_grads(), {1.0/4, 1.0/5, 1.0/6}, "gradients of vec1"); //(vec2^(-1))->get_values()
    compare_vectors(vec2->get_grads(), {-2.0/16, -3.0/25, -4.0/36}, "gradients of vec2");//(-(vec2^(-2)) * vec1)->get_values()
    compare_vectors(vec3->get_grads(), {1, 1, 1}, "gradients of vec3");
    compare_vectors(vec3->get_values(), {1.0/2, 3.0/5, 4.0/6}, "results");
}

TEST_F(BasicOperationTest, SubtractionTest) { 
    std::shared_ptr<Vector> vec3 = vec1 - vec2;
    vec3->backward();

    compare_vectors(vec1->get_grads(), {1, 1, 1}, "gradients of vec1");
    compare_vectors(vec2->get_grads(), {-1, -1, -1}, "gradients of vec2");
    compare_vectors(vec3->get_grads(), {1, 1, 1}, "gradients of vec3");
    compare_vectors(vec3->get_values(), {-2, -2, -2}, "results");
}

struct ManyOperationTest : public testing::Test {
    void compare_vectors(std::vector<float> v, std::vector<float> expected, std::string name){
        ASSERT_EQ(v.size(), expected.size()) << name <<" are of unequal length";

        for (int i = 0; i < v.size(); ++i) {
            EXPECT_EQ(v[i], expected[i]) << name << " differ at index " << i;
        }
    }
};

TEST_F(ManyOperationTest, TrapeziumAreaTest){
    std::shared_ptr<Vector> a = create_vector({2.0, 3.0}, "a");
    std::shared_ptr<Vector> b = create_vector({3.0, 5.5}, "b");
    std::shared_ptr<Vector> h = create_vector({4.0, 18}, "h");
    std::shared_ptr<Vector> two = create_vector({2.0}, "2");
    std::shared_ptr<Vector> area = (a + b) * h / two;
    area->backward();

    compare_vectors(a->get_grads(), {2, 9}, "gradients of a");
    compare_vectors(b->get_grads(), {2, 9}, "gradients of b");
    compare_vectors(h->get_grads(), {2.5, 4.25}, "gradients of h");
    compare_vectors(two->get_grads(), {-5, -38.25}, "gradients of two");
    compare_vectors(area->get_grads(), {1, 1}, "gradients of area");
    compare_vectors(area->get_values(), {10, 76.5}, "results");
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}