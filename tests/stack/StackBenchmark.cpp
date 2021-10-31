#include "stack/StackBenchmark.hpp"

const size_t StackBenchmark::loop_count = 10000;

StackBenchmark::StackBenchmark() : timer(Timer()), original_vec()
{
    for (size_t i = 0; i < loop_count; i++)
    {
        original_vec.push_back(i);
    }
}

void StackBenchmark::test_all()
{
    test_top();
    test_push();
    test_pop();
}

void StackBenchmark::test_top()
{
    ft::stack<int, ft::vector<int> > stk(original_vec);
    timer.start();
    for (size_t i = 0; i < loop_count; i++)
    {
        stk.top();
    }
    timer.stop();
    print_time("stack::top", timer);
}

void StackBenchmark::test_push()
{
    ft::vector<int> empty_vec;
    ft::stack<int, ft::vector<int> > stk(empty_vec);
    timer.start();
    for (size_t i = 0; i < loop_count; i++)
    {
        stk.push(i);
    }
    timer.stop();
    print_time("stack::push", timer);
}

void StackBenchmark::test_pop()
{
    ft::stack<int, ft::vector<int> > stk(original_vec);
    timer.start();
    for (size_t i = 0; i < loop_count; i++)
    {
        stk.pop();
    }
    timer.stop();
    print_time("stack::pop", timer);
}
