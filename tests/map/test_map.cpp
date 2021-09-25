#include "map/test_map.hpp"
#include "map/PairTester.hpp"
#include "map/MapTester.hpp"

void test_map()
{
    PairTester pairTester;
    pairTester.test_all();

    ft::pair<const int, int> elements[] = {
        ft::make_pair(-1, 1),
        ft::make_pair(2, 4),
        ft::make_pair(3, 9),
        ft::make_pair(4, 16)
    };
    size_t elements_len = sizeof(elements) / sizeof(elements[0]);
    MapTester<int, int> mapTester(elements, elements_len);
    mapTester.test_all();
}
