#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>

#ifndef IS_FT
#define IS_FT 0
#endif

#if IS_FT
#include <vector.hpp>
#include <map.hpp>
#include <stack.hpp>
#include <utility.hpp>
// CREATE A REAL STL EXAMPLE
#else
#include <vector>
#include <map>
#include <stack>
namespace ft = std;
#endif

#include "common/Foo.hpp"
#include "common/MyAllocator.hpp"
#include "common/print.hpp"
#include "common/Timer.hpp"
#include "vector/test_vector.hpp"
#include "map/test_map.hpp"
#include "stack/test_stack.hpp"

#endif /* TEST_HPP */
