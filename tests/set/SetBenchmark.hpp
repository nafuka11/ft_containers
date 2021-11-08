#ifndef SETBENCHMARK_HPP
#define SETBENCHMARK_HPP

#include "test.hpp"

class SetBenchmark
{
public:
    SetBenchmark();
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
    void test_empty();
    void test_size();
    void test_max_size();

    // Modifiers
    void test_insert();
    void test_erase();
    void test_swap();
    void test_clear();

    // Observers
    void test_key_comp();
    void test_value_comp();

    // Operations
    void test_find();
    void test_count();
    void test_lower_bound();
    void test_upper_bound();
    void test_equal_range();

    // Allocator
    void test_get_allocator();
};

#endif /* SETBENCHMARK_HPP */
