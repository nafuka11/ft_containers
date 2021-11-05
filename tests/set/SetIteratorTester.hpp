#ifndef SETITERATORTESTER_HPP
#define SETITERATORTESTER_HPP

#include "test.hpp"

template <class T>
class SetIteratorTester
{
public:
    SetIteratorTester(T items[], size_t items_len)
        : s_(items, items + items_len) {}
    ~SetIteratorTester() {}
    void test_all()
    {
        typename ft::set<T>::iterator begin = s_.begin();
        typename ft::set<T>::iterator end = s_.end();
        typename ft::set<T>::const_iterator cbegin = s_.begin();
        typename ft::set<T>::const_iterator cend = s_.end();
        typename ft::set<T>::reverse_iterator rbegin = s_.rbegin();
        typename ft::set<T>::reverse_iterator rend = s_.rend();
        typename ft::set<T>::const_reverse_iterator crbegin = s_.rbegin();
        typename ft::set<T>::const_reverse_iterator crend = s_.rend();

        test_iterator(begin, end);
        test_iterator(rbegin, rend);
        test_iterator(cbegin, cend);
        test_iterator(crbegin, crend);
    }
private:
    ft::set<T> s_;

    template <class Iter>
    void test_iterator(Iter begin, Iter end)
    {
        test_equality_inequality_operator(begin, end);
        test_increment_decrement(begin, end);
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
        Iter prev_end = end;
        Iter next_begin = begin;
        --prev_end;
        ++next_begin;
        print_test_case("++iter");
        {
            Iter iter = begin;
            while (iter != prev_end)
            {
                print_iter(++iter, end);
                std::cout << " ";
            }
            std::cout << std::endl;
        }
        print_test_case("iter++");
        {
            Iter iter = begin;
            while (iter != end)
            {
                print_iter(iter++, end);
                std::cout << " ";
            }
            std::cout << std::endl;
        }
        print_test_case("--iter");
        {
            Iter iter = prev_end;
            while (iter != next_begin)
            {
                print_iter(--iter, end);
                std::cout << " ";
            }
            std::cout << std::endl;
        }
        print_test_case("iter--");
        {
            Iter iter = prev_end;
            while (iter != begin)
            {
                print_iter(iter--, end);
                std::cout << " ";
            }
            std::cout << std::endl;
        }
    }

    template <class Iter>
    void print_iter(Iter iter, Iter end) const
    {
        std::cout << "Iter:";
        if (iter == end)
            std::cout << "end";
        else
            std::cout << *iter;
    }
};

#endif /* SETITERATORTESTER_HPP */
