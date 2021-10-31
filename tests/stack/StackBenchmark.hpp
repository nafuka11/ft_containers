#ifndef STACKBENCHMARK_HPP
#define STACKBENCHMARK_HPP

#include "test.hpp"

class StackBenchmark
{
public:
    StackBenchmark();
    void test_all();

private:
    static const size_t loop_count;
    Timer timer;
    ft::vector<int> original_vec;

    void test_top();
    void test_push();
    void test_pop();
};

#endif /* STACKBENCHMARK_HPP */
