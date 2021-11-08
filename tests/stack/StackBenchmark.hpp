#ifndef STACKBENCHMARK_HPP
#define STACKBENCHMARK_HPP

#include "test.hpp"

class StackBenchmark
{
public:
    StackBenchmark();
    void test_all();

private:
    static const size_t LOOP_COUNT;
    Timer timer_;
    ft::vector<int> original_vec_;

    void test_empty();
    void test_size();
    void test_top();
    void test_push();
    void test_pop();
};

#endif /* STACKBENCHMARK_HPP */
