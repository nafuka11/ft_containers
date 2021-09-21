#include "map/test_map.hpp"
#include "map/PairTester.hpp"
#include "map/MapTester.hpp"

void test_map()
{
    PairTester pairTester;
    pairTester.test_all();

    MapTester<int, int> mapTester;
    mapTester.test_all();
}
