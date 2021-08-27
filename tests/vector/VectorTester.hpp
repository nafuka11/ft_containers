#ifndef VECTORTESTER_HPP
#define VECTORTESTER_HPP

#include <iostream>
#include "common.hpp"

template <class T>
class VectorTester
{
public:
    VectorTester(ft::vector<T> &vec): originalVec(vec) {}
    ~VectorTester() {}
    void test_all()
    {
        test_max_size();
    }

private:
    ft::vector<T> originalVec;

    void print_vector_info(ft::vector<T> &vec)

    void test_max_size()
    {
        print_test_case("vector::max_size()");
        ft::vector<T> vec;
        std::cout << vec.max_size() << std::endl;
    }

};

#endif /* VECTORTESTER_HPP */
