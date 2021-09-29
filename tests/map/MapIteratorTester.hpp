#ifndef MAPITERATORTESTER_HPP
#define MAPITERATORTESTER_HPP

#include "common.hpp"

template <class Key, class T>
class MapIteratorTester
{
public:
    MapIteratorTester(ft::pair<const Key, T> items[], size_t items_len)
        : m_(items, items + items_len) {}
    ~MapIteratorTester() {}
    void test_all()
    {
        typename ft::map<Key, T>::iterator begin = m_.begin();
        typename ft::map<Key, T>::iterator end = m_.end();
        typename ft::map<Key, T>::const_iterator cbegin = m_.begin();
        typename ft::map<Key, T>::const_iterator cend = m_.end();
        typename ft::map<Key, T>::reverse_iterator rbegin = m_.rbegin();
        typename ft::map<Key, T>::reverse_iterator rend = m_.rend();
        typename ft::map<Key, T>::const_reverse_iterator crbegin = m_.rbegin();
        typename ft::map<Key, T>::const_reverse_iterator crend = m_.rend();

        test_iterator(begin, end);
        test_iterator(rbegin, rend);
        test_iterator(cbegin, cend);
        test_iterator(crbegin, crend);
    }
private:
    ft::map<Key, T> m_;

    template <class Iter>
    void test_iterator(Iter begin, Iter end)
    {
        test_equality_inequality_operator(begin, end);
        test_increment_decrement(begin, end);
        // test_inequality_relational_operator(begin);
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
    void test_inequality_relational_operator(Iter begin)
    {
        print_test_case("<, >, <=, >=");
        {
            Iter first = begin;
            Iter second = first;
            ++second;
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
    void print_iter(Iter iter, Iter end) const
    {
        std::cout << "Iter:";
        if (iter == end)
            std::cout << "end";
        else
            print_pair(*iter);
    }

    template <class Pair>
    void print_pair(Pair &value) const
    {
        std::cout << "(" << value.first << ", " << value.second << ")";
    }
};

#endif /* MAPITERATORTESTER_HPP */
