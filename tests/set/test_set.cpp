#include "set/SetIteratorTester.hpp"
#include "set/SetTester.hpp"
#include "set/SetBenchmark.hpp"

void test_set_output()
{
    int int_elements[] = {
        -1, 2, 3, 4, 5
    };
    size_t int_len = sizeof(int_elements) / sizeof(int_elements[0]);

    Foo foo_elements[] = {
        Foo(0, 7),
        Foo(1, 2),
        Foo(2, 4),
        Foo(3, 0),
        Foo(4, 9),
        Foo(5, 8),
        Foo(6, 5),
        Foo(7, 1),
        Foo(8, 6),
        Foo(9, 3)
    };
    size_t foo_len = sizeof(foo_elements) / sizeof(foo_elements[0]);

    SetIteratorTester<int> iter_tester(int_elements, int_len);
    iter_tester.test_all();

    SetTester<int> basic_set_tester(int_elements, int_len);
    basic_set_tester.test_all();

    SetTester<Foo> foo_set_tester(foo_elements, foo_len);
    foo_set_tester.test_all();
}

void test_set_benchmark()
{
    SetBenchmark tester;
    tester.test_all();
}
