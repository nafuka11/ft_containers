#ifndef VECTORITERATORTESTER_HPP
#define VECTORITERATORTESTER_HPP

#include "common.hpp"

template <class T>
class VectorIteratorTester
{
public:
    VectorIteratorTester(ft::vector<T> &vec) : vec(vec) {}
    ~VectorIteratorTester() {}
    void test_all()
    {
        typename ft::vector<T>::iterator begin = vec.begin();
        typename ft::vector<T>::iterator end = vec.end();
        typename ft::vector<T>::const_iterator cbegin = vec.begin();
        typename ft::vector<T>::const_iterator cend = vec.end();
        typename ft::vector<T>::reverse_iterator rbegin = vec.rbegin();
        typename ft::vector<T>::reverse_iterator rend = vec.rend();
        typename ft::vector<T>::const_reverse_iterator crbegin = vec.rbegin();
        typename ft::vector<T>::const_reverse_iterator crend = vec.rend();

        test_iterator(begin, end);
        test_iterator(rbegin, rend);
        test_iterator(cbegin, cend);
        test_iterator(crbegin, crend);
    }

private:
    ft::vector<T> vec;

    template <class Iter>
    void test_iterator(Iter begin, Iter end)
    {
        test_equality_inequality_operator(begin, end);
        test_increment_decrement(begin, end);
        test_arithmetic_operator(begin, end);
        test_inequality_relational_operator(begin);
        test_compound_assignment_operation(begin, end);
        test_offset_difference_operator(begin);
    }

    template <class Iter>
    void test_equality_inequality_operator(Iter begin, Iter end)
    {
        print_test_case("iter == iter");
        {
            std::cout << std::boolalpha
                      << "begin() == begin(): " << (begin == begin) << std::endl
                      << "begin() ==   end(): " << (begin == end) << std::endl;
        }

        print_test_case("iter != iter");
        {
            std::cout << std::boolalpha
                      << "begin() != begin(): " << (begin != begin) << std::endl
                      << "begin() !=   end(): " << (begin != end) << std::endl;
        }
    }

    template <class Iter>
    void test_increment_decrement(Iter begin, Iter end)
    {
        print_test_case("++iter");
        {
            Iter iter = begin;
            while (iter != end - 1)
            {
                std::cout << *(++iter) << " ";
            }
            std::cout << std::endl;
        }
        print_test_case("iter++");
        {
            Iter iter = begin;
            while (iter != end)
            {
                std::cout << *(iter++) << " ";
            }
            std::cout << std::endl;
        }
        print_test_case("--iter");
        {
            Iter iter = end - 1;
            while (iter != begin + 1)
            {
                std::cout << *(--iter) << " ";
            }
            std::cout << std::endl;
        }
        print_test_case("iter--");
        {
            Iter iter = end - 1;
            while (iter != begin)
            {
                std::cout << *(iter--) << " ";
            }
            std::cout << std::endl;
        }
    }

    template <class Iter>
    void test_arithmetic_operator(Iter begin, Iter end)
    {
        print_test_case("iter + ptrdiff_t(2)");
        std::cout << *(begin + 2) << std::endl;

        print_test_case("ptrdiff_t(2) + iter");
        std::cout << *(2 + begin) << std::endl;

        print_test_case("iter - ptrdiff_t(2)");
        std::cout << *(end - 2) << std::endl;

        print_test_case("iter - iter");
        std::cout << end - begin << std::endl;
    }

    template <class Iter>
    void test_inequality_relational_operator(Iter begin)
    {
        print_test_case("<, >, <=, >=");
        {
            Iter first = begin;
            Iter second = first + 1;
            std::cout << std::boolalpha
                      << "first  < first  = " << (first < first) << std::endl
                      << "first  < second = " << (first < second) << std::endl
                      << "first  > first  = " << (first > first) << std::endl
                      << "second > first  = " << (second > first) << std::endl
                      << "first <= first  = " << (first <= first) << std::endl
                      << "first <= second = " << (first <= second) << std::endl
                      << "second<= first  = " << (second <= first) << std::endl
                      << "first >= first  = " << (first >= first) << std::endl
                      << "first >= second = " << (first >= second) << std::endl
                      << "second>= first  = " << (second >= first) << std::endl;
        }
    }

    template <class Iter>
    void test_compound_assignment_operation(Iter begin, Iter end)
    {
        print_test_case("iter += ptrdiff_t(3)");
        {
            Iter iter = begin;
            iter += 3;
            std::cout << *iter << std::endl;
        }

        print_test_case("iter -= ptrdiff_t(3)");
        {
            Iter iter = end;
            iter -= 3;
            std::cout << *iter << std::endl;
        }
    }

    template <class Iter>
    void test_offset_difference_operator(Iter begin)
    {
        print_test_case("iter[2]");
        {
            std::cout << begin[2] << std::endl;
        }
    }
};

#endif /* VECTORITERATORTESTER_HPP */
