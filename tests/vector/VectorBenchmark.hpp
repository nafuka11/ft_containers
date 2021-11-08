#ifndef VECTORBENCHMARK_HPP
#define VECTORBENCHMARK_HPP

#include "test.hpp"

class VectorBenchmark
{
public:
    VectorBenchmark();
    void test_all();

private:
    static const size_t LOOP_COUNT;
    Timer timer_;

    void test_operator_equal();

    // Iterators
    void test_begin();
    void test_end();
    void test_rbegin();
    void test_rend();

    // Capacity
    void test_size();
    void test_max_size();
    void test_resize();
    void test_capacity();
    void test_empty();
    void test_reserve();

    // Element access
    void test_operator_at();
    void test_at();
    void test_front();
    void test_back();

    // Modifiers
    void test_assign();
    void test_push_back();
    void test_pop_back();
    void test_insert();
    void test_erase();
    void test_swap();
    void test_clear();

    // Allocator
    void test_get_allocator();
};

#endif /* VECTORBENCHMARK_HPP */
