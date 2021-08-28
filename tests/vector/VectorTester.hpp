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
        test_reserve();
        test_subscript_operator();
        test_at();
        test_front_back();
        test_assign();
        test_pop_back();
        test_erase();
        test_clear();
    }

private:
    ft::vector<T> originalVec;

    void print_vector_info(ft::vector<T> &vec)
    {
        std::cout << "size()=" << vec.size() << " capacity()=" << vec.capacity() << std::endl;
    }

    void print_vector_elements(ft::vector<T> &vec)
    {
        for (typename ft::vector<T>::iterator iter = vec.begin(); iter != vec.end(); ++iter)
        {
            std::cout << (*iter) << " ";
        }
        std::cout << std::endl;
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

    void test_reserve()
    {
        print_test_case("vector::reserve()");
        {
            ft::vector<T> vec = originalVec;
            std::cout << "vec.reserve(" << originalVec.size() - 1 << "): ";
            vec.reserve(originalVec.size() - 1);
            print_vector_info(vec);
            print_vector_elements(vec);
        }
        {
            ft::vector<T> vec = originalVec;
            std::cout << "vec.reserve(" << originalVec.size() + 1 << "): ";
            vec.reserve(originalVec.size() + 1);
            print_vector_info(vec);
            print_vector_elements(vec);
        }
        {
            ft::vector<T> vec;
            std::cout << "vector().reserve(42): ";
            vec.reserve(42);
            print_vector_info(vec);
            print_vector_elements(vec);
        }
        {
            ft::vector<T> vec = originalVec;
            std::cout << "vec.reserve(" << vec.max_size() + 1 << "): ";
            try
            {
                vec.reserve(vec.max_size() + 1);
            }
            catch (const std::length_error &e)
            {
                std::cout << e.what();
            }
            std::cout << std::endl;
        }
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

    void test_assign()
    {
        print_test_case("vector::assign()");
        test_assign_range(originalVec.begin(), originalVec.end());
        test_assign_range(originalVec.begin(), originalVec.begin());
        test_assign_range(originalVec.begin(), originalVec.end()-1);
        test_assign_fill(0);
        test_assign_fill(2);
        test_assign_fill(5);
        test_assign_fill(10);
    }

    template <class InputIterator>
    void test_assign_range(InputIterator first, InputIterator last)
    {
        ft::vector<T> vec = originalVec;
        std::cout << "vec.assign(iter(" << (*first) << "), iter(" << (*last) << ")): ";
        vec.assign(first, last);
        print_vector_info(vec);
        print_vector_elements(vec);
    }

    void test_assign_fill(typename ft::vector<T>::size_type count)
    {
        ft::vector<T> vec = originalVec;
        std::cout << "vec.assign(" << count << ", " << vec.back() << "): ";
        vec.assign(count, vec.back());
        print_vector_info(vec);
        print_vector_elements(vec);
    }

    void test_pop_back()
    {
        print_test_case("vector::pop_back()");
        ft::vector<T> vec = originalVec;
        vec.pop_back();
        print_vector_info(vec);
        print_vector_elements(vec);
    }

    void test_erase()
    {
        print_test_case("vector::erase()");
        test_erase_one();
        test_erase_range();
    }

    void test_erase_one()
    {
        for (size_t i = 0; i < originalVec.size(); i++)
        {
            ft::vector<T> vec = originalVec;
            std::cout << "vec.erase(" << *(vec.begin() + i) << "): ";
            std::cout << "result=iter(begin()+" << (vec.erase(vec.begin() + i) - vec.begin()) << ") ";
            print_vector_info(vec);
            print_vector_elements(vec);
        }
    }

    void test_erase_range()
    {
        {
            ft::vector<T> vec = originalVec;
            typename ft::vector<T>::iterator first = vec.begin();
            typename ft::vector<T>::iterator last = vec.end();
            std::cout << "vec.erase(first=iter(" << *first << "), iter(first+" << last - first << ")): ";
            std::cout << "result=iter(begin()+" << (vec.erase(first, last) - vec.begin()) << ") ";
            print_vector_info(vec);
            print_vector_elements(vec);
        }
        {
            ft::vector<T> vec = originalVec;
            typename ft::vector<T>::iterator first = vec.begin() + 1;
            typename ft::vector<T>::iterator last = vec.end() - 1;
            std::cout << "vec.erase(first=iter(" << *first << "), iter(first+" << last - first << ")): ";
            std::cout << "result=iter(begin()+" << (vec.erase(first, last) - vec.begin()) << ") ";
            print_vector_info(vec);
            print_vector_elements(vec);
        }
    }

    void test_clear()
    {
        print_test_case("vector::clear()");
        ft::vector<T> vec = originalVec;
        vec.clear();
        print_vector_info(vec);
    }
};

#endif /* VECTORTESTER_HPP */
