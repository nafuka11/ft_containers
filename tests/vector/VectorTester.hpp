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
    }

private:
    ft::vector<T> originalVec;

    void print_vector_info(ft::vector<T> &vec)
};

#endif /* VECTORTESTER_HPP */
