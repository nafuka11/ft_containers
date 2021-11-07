#include "vector/VectorBenchmark.hpp"

const size_t VectorBenchmark::LOOP_COUNT = 10000;

VectorBenchmark::VectorBenchmark() : timer_(Timer()) {}

void VectorBenchmark::test_all()
{
    test_push_back();
    test_pop_back();
    test_insert();
    test_erase();
    test_clear();
}

void VectorBenchmark::test_push_back()
{
    ft::vector<int> vec;

    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        vec.push_back(i);
    }
    timer_.stop();
    print_time("vector::push_back", timer_);
}

void VectorBenchmark::test_pop_back()
{
    ft::vector<int> vec(LOOP_COUNT);

    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        vec.pop_back();
    }
    timer_.stop();
    print_time("vector::pop_back", timer_);
}

void VectorBenchmark::test_insert()
{
    ft::vector<int> vec;

    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        vec.insert(vec.end(), 42);
    }
    timer_.stop();
    print_time("vector::insert", timer_);
}

void VectorBenchmark::test_erase()
{
    ft::vector<int> vec(LOOP_COUNT);

    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        vec.erase(vec.end() - 1);
    }
    timer_.stop();
    print_time("vector::erase", timer_);
}

void VectorBenchmark::test_clear()
{
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        ft::vector<int> vec(100);
        vec.clear();
    }
    timer_.stop();
    print_time("vector::clear", timer_);
}
