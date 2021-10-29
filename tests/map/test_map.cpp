#include "map/test_map.hpp"
#include "map/PairTester.hpp"
#include "map/MapIteratorTester.hpp"
#include "map/MapTester.hpp"
#include "map/MapBenchmark.hpp"

void test_map_output()
{
    PairTester pairTester;
    pairTester.test_all();

    ft::pair<const int, std::string> int_str_elements[] = {
        ft::make_pair(-1, "A"),
        ft::make_pair(2, "B"),
        ft::make_pair(3, "C"),
        ft::make_pair(4, "D"),
        ft::make_pair(5, "E")
    };
    size_t int_str_len = sizeof(int_str_elements) / sizeof(int_str_elements[0]);
    ft::pair<const Foo, Foo> foo_elements[] = {
        ft::make_pair(Foo(0, 7), Foo(0, 0)),
        ft::make_pair(Foo(1, 2), Foo(1, 1)),
        ft::make_pair(Foo(2, 4), Foo(2, 2)),
        ft::make_pair(Foo(3, 0), Foo(3, 3)),
        ft::make_pair(Foo(4, 9), Foo(4, 4)),
        ft::make_pair(Foo(5, 8), Foo(5, 5)),
        ft::make_pair(Foo(6, 5), Foo(6, 6)),
        ft::make_pair(Foo(7, 1), Foo(7, 7)),
        ft::make_pair(Foo(8, 6), Foo(8, 8)),
        ft::make_pair(Foo(9, 3), Foo(9, 9))
    };
    size_t foo_len = sizeof(foo_elements) / sizeof(foo_elements[0]);

    MapIteratorTester<int, std::string> iter_tester(int_str_elements, int_str_len);
    iter_tester.test_all();

    MapTester<int, std::string> basic_map_tester(int_str_elements, int_str_len);
    basic_map_tester.test_all();

    MapTester<Foo, Foo> foo_map_tester(foo_elements, foo_len);
    foo_map_tester.test_all();
}

void test_map_benchmark()
{
    MapBenchmark tester;
    tester.test_all();
}
