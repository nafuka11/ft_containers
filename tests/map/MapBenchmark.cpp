#include "map/MapBenchmark.hpp"

const size_t MapBenchmark::loop_count = 10000;

MapBenchmark::MapBenchmark() : timer_(Timer()) {}

void MapBenchmark::test_all()
{
    test_operator_at();
    test_begin();
    test_end();
    test_clear();
    test_insert();
    test_erase();
    test_find();
}

void MapBenchmark::test_operator_at()
{
    ft::map<int, int> m;
    for (size_t i = 0; i < loop_count; i++)
    {
        m.insert(ft::make_pair(i, i));
    }
    timer_.start();
    for (size_t i = 0; i < loop_count; i++)
    {
        m[i] = 42;
    }
    timer_.stop();
    print_time("map::operator[]", timer_);
}

void MapBenchmark::test_begin()
{
    ft::map<int, int> m;
    for (int i = 0; i < 10; i++)
    {
        m.insert(ft::make_pair(i, i));
    }
    timer_.start();
    for (size_t i = 0; i < loop_count; i++)
    {
        m.begin();
    }
    timer_.stop();
    print_time("map::begin", timer_);
}

void MapBenchmark::test_end()
{
    ft::map<int, int> m;
    for (size_t i = 0; i < loop_count; i++)
    {
        m.insert(ft::make_pair(i, i));
    }
    timer_.start();
    for (size_t i = 0; i < loop_count; i++)
    {
        m.end();
    }
    timer_.stop();
    print_time("map::end", timer_);
}

void MapBenchmark::test_clear()
{
    ft::map<int, int> m;
    for (size_t i = 0; i < loop_count; i++)
    {
        m.insert(ft::make_pair(i, i));
    }
    timer_.start();
    m.clear();
    timer_.stop();
    print_time("map::clear", timer_);
}

void MapBenchmark::test_insert()
{
    ft::map<int, int> m;
    timer_.start();
    for (size_t i = 0; i < loop_count; i++)
    {
        m.insert(ft::make_pair(i, i));
    }
    timer_.stop();
    print_time("map::insert", timer_);
}

void MapBenchmark::test_erase()
{
    ft::map<int, int> m;
    for (size_t i = 0; i < loop_count; i++)
    {
        m.insert(ft::make_pair(i, i));
    }
    timer_.start();
    for (size_t i = 0; i < loop_count; i++)
    {
        m.erase(i);
    }
    timer_.stop();
    print_time("map::erase", timer_);
}

void MapBenchmark::test_find()
{
    ft::map<int, int> m;
    for (size_t i = 0; i < loop_count; i++)
    {
        m.insert(ft::make_pair(i, i));
    }
    timer_.start();
    for (size_t i = 0; i < loop_count; i++)
    {
        m.find(i);
    }
    timer_.stop();
    print_time("map::find", timer_);
}
