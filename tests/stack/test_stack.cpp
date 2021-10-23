#include <list>
#include "stack/StackTester.hpp"

void test_stack()
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

    StackTester<int, ft::vector<int> > vector_stack_tester(vec, 42);
    StackTester<int, std::list<int> > list_stack_tester(lst, 42);

    vector_stack_tester.test_all();
    list_stack_tester.test_all();
}
