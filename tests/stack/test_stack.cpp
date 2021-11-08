#include <list>
#include <deque>
#include "stack/StackBenchmark.hpp"
#include "stack/StackTester.hpp"

void test_stack_output()
{
    ft::vector<int> vec(5);
    for (size_t i = 0; i < vec.size(); i++)
    {
        vec[i] = i + 1;
    }

    std::list<int> lst;
    for (size_t i = 0; i < 10; i++)
    {
        lst.push_back(i + 1);
    }

    std::deque<int> deq;
    for (size_t i = 0; i < 42; i++)
    {
        deq.push_back(i * 2);
    }

    StackTester<int, ft::vector<int> > vector_stack_tester(vec, 42);
    StackTester<int, std::list<int> > list_stack_tester(lst, 42);
    StackTester<int, std::deque<int> > deque_stack_tester(deq, 42);

    vector_stack_tester.test_all();
    list_stack_tester.test_all();
    deque_stack_tester.test_all();
}

void test_stack_benchmark()
{
    StackBenchmark tester;
    tester.test_all();
}
