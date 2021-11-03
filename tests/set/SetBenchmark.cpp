#include "set/SetBenchmark.hpp"

const size_t SetBenchmark::LOOP_COUNT = 10000;

SetBenchmark::SetBenchmark() : timer_(Timer()) {}

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
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        s.insert(i);
    }
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        s.begin();
    }
    timer_.stop();
    print_time("set::begin", timer_);
}

void SetBenchmark::test_end()
{
    ft::set<int> s;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        s.insert(i);
    }
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        s.begin();
    }
    timer_.stop();
    print_time("set::end", timer_);
}

void SetBenchmark::test_clear()
{
    ft::set<int> s;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        s.insert(i);
    }
    timer_.start();
    s.clear();
    timer_.stop();
    print_time("set::clear", timer_);
}

void SetBenchmark::test_insert()
{
    ft::set<int> s;
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        s.insert(i);
    }
    timer_.stop();
    print_time("set::insert", timer_);
}

void SetBenchmark::test_erase()
{
    ft::set<int> s;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        s.insert(i);
    }
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        s.erase(i);
    }
    timer_.stop();
    print_time("set::erase", timer_);
}

void SetBenchmark::test_find()
{
    ft::set<int> s;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        s.insert(i);
    }
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        s.find(i);
    }
    timer_.stop();
    print_time("set::find", timer_);
}
