#include "set/SetBenchmark.hpp"

const size_t SetBenchmark::LOOP_COUNT = 10000;

SetBenchmark::SetBenchmark() : timer_(Timer()) {}

void SetBenchmark::test_all()
{
    test_operator_equal();

    // Iterators
    test_begin();
    test_end();
    test_rbegin();
    test_rend();

    // Capacity
    test_empty();
    test_size();
    test_max_size();

    // Modifiers
    test_insert();
    test_erase();
    test_swap();
    test_clear();

    // Observers
    test_key_comp();
    test_value_comp();

    // Operations
    test_find();
    test_count();
    test_lower_bound();
    test_upper_bound();
    test_equal_range();

    // Allocator
    test_get_allocator();
}

void SetBenchmark::test_operator_equal()
{
    ft::set<int> src, dest;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        src.insert(i);
    }
    timer_.start();
    dest = src;
    timer_.stop();
    print_time("set::operator=", timer_);
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

void SetBenchmark::test_rbegin()
{
    ft::set<int> s;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        s.insert(i);
    }
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        s.rbegin();
    }
    timer_.stop();
    print_time("set::rbegin", timer_);
}

void SetBenchmark::test_rend()
{
    ft::set<int> s;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        s.insert(i);
    }
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        s.rend();
    }
    timer_.stop();
    print_time("set::rend", timer_);
}

void SetBenchmark::test_empty()
{
    ft::set<int> s_empty, s_one;
    s_one.insert(42);
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        s_empty.empty();
        s_one.empty();
    }
    timer_.stop();
    print_time("set::empty", timer_);
}

void SetBenchmark::test_size()
{
    ft::set<int> s;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        s.insert(i);
    }
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        s.size();
    }
    timer_.stop();
    print_time("set::size", timer_);
}

void SetBenchmark::test_max_size()
{
    ft::set<int> s;
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        s.max_size();
    }
    timer_.stop();
    print_time("set::max_size", timer_);
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

void SetBenchmark::test_swap()
{
    ft::set<int> s1, s2;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        s1.insert(i);
        s2.insert(i * 2);
    }
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        s1.swap(s2);
    }
    timer_.stop();
    print_time("set::swap", timer_);
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

void SetBenchmark::test_key_comp()
{
    ft::set<int> s;
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        s.key_comp();
    }
    timer_.stop();
    print_time("set::key_comp", timer_);
}

void SetBenchmark::test_value_comp()
{
    ft::set<int> s;
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        s.value_comp();
    }
    timer_.stop();
    print_time("set::value_comp", timer_);
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
        s.find(LOOP_COUNT);
    }
    timer_.stop();
    print_time("set::find", timer_);
}

void SetBenchmark::test_count()
{
    ft::set<int> s;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        s.insert(i);
    }
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        s.count(i);
        s.count(LOOP_COUNT);
    }
    timer_.stop();
    print_time("set::count", timer_);
}

void SetBenchmark::test_lower_bound()
{
    ft::set<int> s;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        s.insert(i);
    }
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        s.lower_bound(i);
        s.lower_bound(LOOP_COUNT);
    }
    timer_.stop();
    print_time("set::lower_bound", timer_);
}

void SetBenchmark::test_upper_bound()
{
    ft::set<int> s;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        s.insert(i);
    }
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        s.upper_bound(i);
        s.upper_bound(LOOP_COUNT);
    }
    timer_.stop();
    print_time("set::upper_bound", timer_);
}

void SetBenchmark::test_equal_range()
{
    ft::set<int> s;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        s.insert(i);
    }
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        s.equal_range(i);
        s.equal_range(LOOP_COUNT);
    }
    timer_.stop();
    print_time("set::equal_range", timer_);
}

void SetBenchmark::test_get_allocator()
{
    ft::set<int> s;
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        s.get_allocator();
    }
    timer_.stop();
    print_time("set::get_allocator", timer_);
}
