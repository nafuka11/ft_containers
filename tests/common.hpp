#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>

#ifndef IS_FT
#define IS_FT 0
#endif

#if IS_FT
#include <map.hpp>
// #include <stack.hpp>
#include <vector.hpp>
#include <utility.hpp>
// CREATE A REAL STL EXAMPLE
#else
#include <map>
#include <stack>
#include <vector>
namespace ft = std;
#endif

#include "common/Foo.hpp"
#include "common/MyAllocator.hpp"
#include "common/print.hpp"
#include "map/test_map.hpp"
#include "vector/test_vector.hpp"

#endif /* COMMON_HPP */
