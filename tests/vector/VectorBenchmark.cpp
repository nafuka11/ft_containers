#include "vector/VectorBenchmark.hpp"

const size_t VectorBenchmark::loop_count = 10000;

VectorBenchmark::VectorBenchmark() : timer_(Timer()) {}

void VectorBenchmark::test_all()
{
    test_clear();
    test_insert();
    test_erase();
    test_push_back();
    test_pop_back();
}

void VectorBenchmark::test_clear()
{
    timer_.start();
    for (size_t i = 0; i < loop_count; i++)
    {
        ft::vector<int> vec(100);
        vec.clear();
    }
    timer_.stop();
    print_time("vector::clear", timer_);
}

void VectorBenchmark::test_insert()
{
    ft::vector<int> vec;

    timer_.start();
    for (size_t i = 0; i < loop_count; i++)
    {
        vec.insert(vec.end(), 42);
    }
    timer_.stop();
    print_time("vector::insert", timer_);
}

void VectorBenchmark::test_erase()
{
    ft::vector<int> vec(loop_count);

    timer_.start();
    for (size_t i = 0; i < loop_count; i++)
    {
        vec.erase(vec.end() - 1);
    }
    timer_.stop();
    print_time("vector::erase", timer_);
}

void VectorBenchmark::test_push_back()
{
    ft::vector<int> vec;

    timer_.start();
    for (size_t i = 0; i < loop_count; i++)
    {
        vec.push_back(i);
    }
    timer_.stop();
    print_time("vector::push_back", timer_);
}

void VectorBenchmark::test_pop_back()
{
    ft::vector<int> vec(loop_count);

    timer_.start();
    for (size_t i = 0; i < loop_count; i++)
    {
        vec.pop_back();
    }
    timer_.stop();
    print_time("vector::pop_back", timer_);
}
