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
        test_empty();
        test_subscript_operator();
        test_at();
        test_front_back();
    }

private:
    ft::vector<T> originalVec;

    void print_vector_info(ft::vector<T> &vec)
    {
        std::cout << "size()=" << vec.size() << " capacity()=" << vec.capacity() << std::endl;
    }


    void test_max_size()
    {
        print_test_case("vector::max_size()");
        ft::vector<T> vec;
        std::cout << vec.max_size() << std::endl;
    }

    void test_empty()
    {
        print_test_case("vector::empty()");
        ft::vector<T> vecEmpty;
        std::cout << std::boolalpha << "vector().empty()=" << vecEmpty.empty() << std::endl;
        ft::vector<T> vecOne(1);
        std::cout << std::boolalpha << "vector(1).empty()=" << vecOne.empty() << std::endl;
    }

    void test_subscript_operator()
    {
        print_test_case("vector::operator[]");
        for (size_t i = 0; i < originalVec.size(); i++)
        {
            std::cout << "vec[" << i << "]=" << originalVec[i] << " ";
        }
        std::cout << std::endl;
    }

    void test_at()
    {
        print_test_case("vector::at()");
        for (size_t i = 0; i < originalVec.size() + 1; i++)
        {
            try
            {
                std::cout << "vec.at(" << i << ")=";
                std::cout << originalVec.at(i) << " ";
            }
            catch(const std::out_of_range &e)
            {
                std::cout << e.what() << " ";
            }
        }
        std::cout << std::endl;
    }

    void test_front_back()
    {
        print_test_case("vector::front(), back()");
        std::cout << "vec.front()=" << originalVec.front() << std::endl;
        std::cout << "vec.back() =" << originalVec.back() << std::endl;
    }
};

#endif /* VECTORTESTER_HPP */
