#include "test.hpp"
#include "map/MapBenchmark.hpp"

const int MapBenchmark::loop_count = 10000;

MapBenchmark::MapBenchmark(): timer(Timer()) {}

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
    for (int i = 0; i < loop_count; i++)
    {
        m.insert(ft::make_pair(i, i));
    }
    timer.start();
    for (int i = 0; i < loop_count; i++)
    {
        m[i] = 42;
    }
    timer.stop();
    print_time("map::operator[]", timer);
}

void MapBenchmark::test_begin()
{
    ft::map<int, int> m;
    for (int i = 0; i < 10; i++)
    {
        m.insert(ft::make_pair(i, i));
    }
    timer.start();
    for (int i = 0; i < loop_count; i++)
    {
        m.begin();
    }
    timer.stop();
    print_time("map::begin", timer);
}

void MapBenchmark::test_end()
{
    ft::map<int, int> m;
    for (int i = 0; i < loop_count; i++)
    {
        m.insert(ft::make_pair(i, i));
    }
    timer.start();
    for (int i = 0; i < loop_count; i++)
    {
        m.end();
    }
    timer.stop();
    print_time("map::end", timer);
}

void MapBenchmark::test_clear()
{
    ft::map<int, int> m;
    for (int i = 0; i < loop_count; i++)
    {
        m.insert(ft::make_pair(i, i));
    }
    timer.start();
    m.clear();
    timer.stop();
    print_time("map::clear", timer);
}

void MapBenchmark::test_insert()
{
    ft::map<int, int> m;
    timer.start();
    for (int i = 0; i < loop_count; i++)
    {
        m.insert(ft::make_pair(i, i));
    }
    timer.stop();
    print_time("map::insert", timer);
}

void MapBenchmark::test_erase()
{
    ft::map<int, int> m;
    for (int i = 0; i < loop_count; i++)
    {
        m.insert(ft::make_pair(i, i));
    }
    timer.start();
    for (int i = 0; i < loop_count; i++)
    {
        m.erase(i);
    }
    timer.stop();
    print_time("map::erase", timer);
}

void MapBenchmark::test_find()
{
    ft::map<int, int> m;
    for (int i = 0; i < loop_count; i++)
    {
        m.insert(ft::make_pair(i, i));
    }
    timer.start();
    for (int i = 0; i < loop_count; i++)
    {
        m.find(i);
    }
    timer.stop();
    print_time("map::find", timer);
}
