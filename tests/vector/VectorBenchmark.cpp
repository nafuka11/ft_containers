#include "vector/VectorBenchmark.hpp"

const size_t VectorBenchmark::LOOP_COUNT = 10000;

VectorBenchmark::VectorBenchmark() : timer_(Timer()) {}

void VectorBenchmark::test_all()
{
    test_operator_equal();

    // Iterators
    test_begin();
    test_end();
    test_rbegin();
    test_rend();

    // Capacity
    test_size();
    test_max_size();
    test_resize();
    test_capacity();
    test_empty();
    test_reserve();

    // Element access
    test_operator_at();
    test_at();
    test_front();
    test_back();

    // Modifiers
    test_assign();
    test_push_back();
    test_pop_back();
    test_insert();
    test_erase();
    test_swap();
    test_clear();

    // Allocator
    test_get_allocator();
}

void VectorBenchmark::test_operator_equal()
{
    ft::vector<int> src, dest;

    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        src.push_back(i);
    }
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        dest = src;
    }
    timer_.stop();
    print_time("vector::operator=", timer_);
}

void VectorBenchmark::test_begin()
{
    ft::vector<int> vec;

    for (size_t i = 0; i < 10; i++)
    {
        vec.push_back(i);
    }
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        vec.begin();
    }
    timer_.stop();
    print_time("vector::begin", timer_);
}

void VectorBenchmark::test_end()
{
    ft::vector<int> vec;

    for (size_t i = 0; i < 10; i++)
    {
        vec.push_back(i);
    }
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        vec.end();
    }
    timer_.stop();
    print_time("vector::end", timer_);
}

void VectorBenchmark::test_rbegin()
{
    ft::vector<int> vec;

    for (size_t i = 0; i < 10; i++)
    {
        vec.push_back(i);
    }
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        vec.rbegin();
    }
    timer_.stop();
    print_time("vector::rbegin", timer_);
}

void VectorBenchmark::test_rend()
{
    ft::vector<int> vec;

    for (size_t i = 0; i < 10; i++)
    {
        vec.push_back(i);
    }
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        vec.rend();
    }
    timer_.stop();
    print_time("vector::rend", timer_);
}

void VectorBenchmark::test_size()
{
    ft::vector<int> vec;

    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        vec.push_back(i);
    }
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        vec.size();
    }
    timer_.stop();
    print_time("vector::size", timer_);
}

void VectorBenchmark::test_max_size()
{
    ft::vector<int> vec;

    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        vec.max_size();
    }
    timer_.stop();
    print_time("vector::max_size", timer_);
}

void VectorBenchmark::test_resize()
{
    ft::vector<int> vec;

    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        vec.resize(i, 42);
    }
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        vec.resize(LOOP_COUNT - i);
    }
    timer_.stop();
    print_time("vector::resize", timer_);
}

void VectorBenchmark::test_capacity()
{
    ft::vector<int> vec;

    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        vec.push_back(i);
    }
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        vec.capacity();
    }
    timer_.stop();
    print_time("vector::capacity", timer_);
}

void VectorBenchmark::test_empty()
{
    ft::vector<int> vec_empty;
    ft::vector<int> vec_one;
    vec_one.push_back(42);

    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT / 2; i++)
    {
        vec_empty.empty();
        vec_one.empty();
    }
    timer_.stop();
    print_time("vector::empty", timer_);
}

void VectorBenchmark::test_reserve()
{
    ft::vector<int> vec;

    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        vec.reserve(i);
    }
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        vec.reserve(LOOP_COUNT - i);
    }
    timer_.stop();
    print_time("vector::reserve", timer_);
}

void VectorBenchmark::test_operator_at()
{
    ft::vector<int> vec;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        vec.push_back(i);
    }

    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        vec[i] = 42;
    }
    timer_.stop();
    print_time("vector::operator=", timer_);
}

void VectorBenchmark::test_at()
{
    ft::vector<int> vec;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        vec.push_back(i);
    }

    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        vec.at(i) = 42;
    }
    timer_.stop();
    print_time("vector::at", timer_);
}

void VectorBenchmark::test_front()
{
    ft::vector<int> vec;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        vec.push_back(i);
    }

    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        vec.front();
    }
    timer_.stop();
    print_time("vector::front", timer_);
}

void VectorBenchmark::test_back()
{
    ft::vector<int> vec;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        vec.push_back(i);
    }

    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        vec.back();
    }
    timer_.stop();
    print_time("vector::back", timer_);
}

void VectorBenchmark::test_assign()
{
    ft::vector<int> vec;

    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        vec.assign(42, 21);
    }
    timer_.stop();
    print_time("vector::assign", timer_);
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

void VectorBenchmark::test_swap()
{
    ft::vector<int> src(LOOP_COUNT, 42);
    ft::vector<int> dest(LOOP_COUNT, 21);

    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        src.swap(dest);
    }
    timer_.stop();
    print_time("vector::swap", timer_);
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

void VectorBenchmark::test_get_allocator()
{
    ft::vector<int> vec;

    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        vec.get_allocator();
    }
    timer_.stop();
    print_time("vector::get_allocator", timer_);
}
