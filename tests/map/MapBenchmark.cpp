#include "map/MapBenchmark.hpp"

const size_t MapBenchmark::LOOP_COUNT = 10000;

MapBenchmark::MapBenchmark() : timer_(Timer()) {}

void MapBenchmark::test_all()
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

    // Element access
    test_operator_at();

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

void MapBenchmark::test_operator_equal()
{
    ft::map<int, int> src, dest;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        src.insert(ft::make_pair(i, i));
    }
    timer_.start();
    dest = src;
    timer_.stop();
    print_time("map::operator=", timer_);
}

void MapBenchmark::test_begin()
{
    ft::map<int, int> m;
    for (int i = 0; i < 10; i++)
    {
        m.insert(ft::make_pair(i, i));
    }
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        m.begin();
    }
    timer_.stop();
    print_time("map::begin", timer_);
}

void MapBenchmark::test_end()
{
    ft::map<int, int> m;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        m.insert(ft::make_pair(i, i));
    }
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        m.end();
    }
    timer_.stop();
    print_time("map::end", timer_);
}

void MapBenchmark::test_rbegin()
{
    ft::map<int, int> m;
    for (int i = 0; i < 10; i++)
    {
        m.insert(ft::make_pair(i, i));
    }
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        m.rbegin();
    }
    timer_.stop();
    print_time("map::rbegin", timer_);
}

void MapBenchmark::test_rend()
{
    ft::map<int, int> m;
    for (int i = 0; i < 10; i++)
    {
        m.insert(ft::make_pair(i, i));
    }
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        m.rend();
    }
    timer_.stop();
    print_time("map::rend", timer_);
}

void MapBenchmark::test_empty()
{
    ft::map<int, int> m_empty;
    ft::map<int, int> m_one;
    m_one.insert(ft::make_pair(42, 42));
    timer_.start();

    for (size_t i = 0; i < LOOP_COUNT / 2; i++)
    {
        m_empty.empty();
        m_one.empty();
    }
    timer_.stop();
    print_time("map::empty", timer_);
}

void MapBenchmark::test_size()
{
    ft::map<int, int> m;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        m.insert(ft::make_pair(i, i));
    }
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        m.size();
    }
    timer_.stop();
    print_time("map::size", timer_);
}

void MapBenchmark::test_max_size()
{
    ft::map<int, int> m;
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        m.max_size();
    }
    timer_.stop();
    print_time("map::max_size", timer_);
}

void MapBenchmark::test_operator_at()
{
    ft::map<int, int> m;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        m.insert(ft::make_pair(i, i));
    }
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        m[i] = 42;
    }
    timer_.stop();
    print_time("map::operator[]", timer_);
}

void MapBenchmark::test_insert()
{
    ft::map<int, int> m;
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        m.insert(ft::make_pair(i, i));
    }
    timer_.stop();
    print_time("map::insert", timer_);
}

void MapBenchmark::test_erase()
{
    ft::map<int, int> m;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        m.insert(ft::make_pair(i, i));
    }
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        m.erase(i);
    }
    timer_.stop();
    print_time("map::erase", timer_);
}

void MapBenchmark::test_swap()
{
    ft::map<int, int> m1;
    ft::map<int, int> m2;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        m1.insert(ft::make_pair(i, i));
        m2.insert(ft::make_pair(i * 2, i * 2));
    }
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        m1.swap(m2);
    }
    timer_.stop();
    print_time("map::swap", timer_);
}

void MapBenchmark::test_clear()
{
    ft::map<int, int> m;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        m.insert(ft::make_pair(i, i));
    }
    timer_.start();
    m.clear();
    timer_.stop();
    print_time("map::clear", timer_);
}

void MapBenchmark::test_key_comp()
{
    ft::map<int, int> m;
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        m.key_comp();
    }
    timer_.stop();
    print_time("map::key_comp", timer_);
}

void MapBenchmark::test_value_comp()
{
    ft::map<int, int> m;
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        m.value_comp();
    }
    timer_.stop();
    print_time("map::value_comp", timer_);
}

void MapBenchmark::test_find()
{
    ft::map<int, int> m;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        m.insert(ft::make_pair(i, i));
    }
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        m.find(i);
        m.find(LOOP_COUNT);
    }
    timer_.stop();
    print_time("map::find", timer_);
}

void MapBenchmark::test_count()
{
    ft::map<int, int> m;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        m.insert(ft::make_pair(i, i));
    }
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        m.count(i);
        m.count(LOOP_COUNT);
    }
    timer_.stop();
    print_time("map::count", timer_);
}

void MapBenchmark::test_lower_bound()
{
    ft::map<int, int> m;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        m.insert(ft::make_pair(i, i));
    }
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        m.lower_bound(i);
        m.lower_bound(LOOP_COUNT);
    }
    timer_.stop();
    print_time("map::lower_bound", timer_);
}

void MapBenchmark::test_upper_bound()
{
    ft::map<int, int> m;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        m.insert(ft::make_pair(i, i));
    }
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        m.upper_bound(i);
        m.upper_bound(LOOP_COUNT);
    }
    timer_.stop();
    print_time("map::upper_bound", timer_);
}

void MapBenchmark::test_equal_range()
{
    ft::map<int, int> m;
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        m.insert(ft::make_pair(i, i));
    }
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        m.equal_range(i);
        m.equal_range(LOOP_COUNT);
    }
    timer_.stop();
    print_time("map::equal_range", timer_);
}

void MapBenchmark::test_get_allocator()
{
    ft::map<int, int> m;
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        m.get_allocator();
    }
    timer_.stop();
    print_time("map::get_allocator", timer_);
}
