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

    void test_clear();
    void test_insert();
    void test_erase();
    void test_push_back();
    void test_pop_back();
};

#endif /* VECTORBENCHMARK_HPP */
