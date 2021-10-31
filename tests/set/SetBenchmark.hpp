#ifndef SETBENCHMARK_HPP
#define SETBENCHMARK_HPP

#include "test.hpp"

class SetBenchmark
{
public:
    SetBenchmark();
    void test_all();

private:
    static const int loop_count;
    Timer timer;

    void test_begin();
    void test_end();
    void test_clear();
    void test_insert();
    void test_erase();
    void test_find();
};

#endif /* SETBENCHMARK_HPP */
