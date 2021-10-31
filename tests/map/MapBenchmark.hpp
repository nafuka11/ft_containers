#ifndef MAPBENCHMARK_HPP
#define MAPBENCHMARK_HPP

#include "test.hpp"

class MapBenchmark
{
public:
    MapBenchmark();
    void test_all();

private:
    static const size_t loop_count;
    Timer timer;

    void test_operator_at();
    void test_begin();
    void test_end();
    void test_clear();
    void test_insert();
    void test_erase();
    void test_find();
};

#endif /* MAPBENCHMARK_HPP */
