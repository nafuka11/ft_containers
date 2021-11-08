#include "stack/StackBenchmark.hpp"

const size_t StackBenchmark::LOOP_COUNT = 10000;

StackBenchmark::StackBenchmark() : timer_(Timer()), original_vec_()
{
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        original_vec_.push_back(i);
    }
}

void StackBenchmark::test_all()
{
    test_empty();
    test_size();
    test_top();
    test_push();
    test_pop();
}

void StackBenchmark::test_empty()
{
    ft::vector<int> empty_vec;
    ft::stack<int, ft::vector<int> > stk(original_vec_), empty_stk(empty_vec);
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        stk.empty();
        empty_stk.empty();
    }
    timer_.stop();
    print_time("stack::empty", timer_);
}

void StackBenchmark::test_size()
{
    ft::stack<int, ft::vector<int> > stk(original_vec_);
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        stk.size();
    }
    timer_.stop();
    print_time("stack::size", timer_);
}

void StackBenchmark::test_top()
{
    ft::stack<int, ft::vector<int> > stk(original_vec_);
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        stk.top();
    }
    timer_.stop();
    print_time("stack::top", timer_);
}

void StackBenchmark::test_push()
{
    ft::vector<int> empty_vec;
    ft::stack<int, ft::vector<int> > stk(empty_vec);
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        stk.push(i);
    }
    timer_.stop();
    print_time("stack::push", timer_);
}

void StackBenchmark::test_pop()
{
    ft::stack<int, ft::vector<int> > stk(original_vec_);
    timer_.start();
    for (size_t i = 0; i < LOOP_COUNT; i++)
    {
        stk.pop();
    }
    timer_.stop();
    print_time("stack::pop", timer_);
}
