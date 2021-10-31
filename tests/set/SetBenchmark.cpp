#include "set/SetBenchmark.hpp"

const size_t SetBenchmark::loop_count = 10000;

SetBenchmark::SetBenchmark() : timer(Timer()) {}

void SetBenchmark::test_all()
{
    test_begin();
    test_end();
    test_clear();
    test_insert();
    test_erase();
    test_find();
}

void SetBenchmark::test_begin()
{
    ft::set<int> s;
    for (size_t i = 0; i < loop_count; i++)
    {
        s.insert(i);
    }
    timer.start();
    for (size_t i = 0; i < loop_count; i++)
    {
        s.begin();
    }
    timer.stop();
    print_time("set::begin", timer);
}

void SetBenchmark::test_end()
{
    ft::set<int> s;
    for (size_t i = 0; i < loop_count; i++)
    {
        s.insert(i);
    }
    timer.start();
    for (size_t i = 0; i < loop_count; i++)
    {
        s.begin();
    }
    timer.stop();
    print_time("set::end", timer);
}

void SetBenchmark::test_clear()
{
    ft::set<int> s;
    for (size_t i = 0; i < loop_count; i++)
    {
        s.insert(i);
    }
    timer.start();
    s.clear();
    timer.stop();
    print_time("set::clear", timer);
}

void SetBenchmark::test_insert()
{
    ft::set<int> s;
    timer.start();
    for (size_t i = 0; i < loop_count; i++)
    {
        s.insert(i);
    }
    timer.stop();
    print_time("set::insert", timer);
}

void SetBenchmark::test_erase()
{
    ft::set<int> s;
    for (size_t i = 0; i < loop_count; i++)
    {
        s.insert(i);
    }
    timer.start();
    for (size_t i = 0; i < loop_count; i++)
    {
        s.erase(i);
    }
    timer.stop();
    print_time("set::erase", timer);
}

void SetBenchmark::test_find()
{
    ft::set<int> s;
    for (size_t i = 0; i < loop_count; i++)
    {
        s.insert(i);
    }
    timer.start();
    for (size_t i = 0; i < loop_count; i++)
    {
        s.find(i);
    }
    timer.stop();
    print_time("set::find", timer);
}
