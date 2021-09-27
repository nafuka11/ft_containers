#ifndef MAPTESTER_HPP
#define MAPTESTER_HPP

#include "common.hpp"

template <class Key, class T>
class MapTester
{
public:
    MapTester() : items_(), items_len_(0) {}
    MapTester(ft::pair<const Key, T> items[], size_t items_len)
        : items_(items), items_len_(items_len) {}
    ~MapTester() {}
    void test_all()
    {
        test_constructor();

        // Capacity
        test_max_size();

        test_insert();

        test_get_allocator();
    }

private:
    ft::pair<const Key, T> *items_;
    size_t items_len_;

    void print_map(ft::map<Key, T> &m)
    {
        std::cout << std::boolalpha
                  << "size=" << m.size() << " empty=" << m.empty() << " items:";
        typename ft::map<Key, T>::iterator iter = m.begin();
        for (size_t i = 0; i < m.size(); i++)
        {
            std::cout << "[" << i << "]=";
            print_pair(*iter);
            ++iter;
            if (i < m.size() - 1)
                std::cout << ", ";
        }
        if (m.size() > 0)
            std::cout << std::endl;
    }

    void print_pair(const ft::pair<const Key, T> &value)
    {
        std::cout << "(" << value.first << ", " << value.second << ")";
    }

    void test_constructor()
    {
        print_test_case("map()");
        ft::map<Key, T> m;
        print_map(m);
    }

    void test_max_size()
    {
        print_test_case("map::max_size()");
        ft::map<Key, T> m;
        std::cout << m.max_size() << std::endl;
    }

    void test_insert()
    {
        print_test_case("map::insert() : single element");
        {
            ft::map<Key, T> m;
            for (size_t i = 0; i < items_len_; i++)
            {
                test_insert_single(m, items_[i]);
            }
            test_insert_single(m, ft::make_pair(items_[0].first, items_[1].second));
        }
        print_test_case("map::insert() : with hint(pos=end(), val=max)");
        {
            ft::map<Key, T> m;
            for (size_t i = 0; i < items_len_; i++)
            {
                test_insert_with_hint(m, m.end(), items_[i]);
            }
        }
        print_test_case("map::insert() : with hint(pos=begin(), val=min)");
        {
            ft::map<Key, T> m;
            for (size_t i = 0; i < items_len_; i++)
            {
                test_insert_with_hint(m, m.begin(), items_[items_len_ - i - 1]);
            }
        }
        print_test_case("map::insert() : with hint(pos=begin()+1, pos-1<val<pos)");
        {
            ft::map<Key, T> m;
            m.insert(items_[0]);
            m.insert(items_[2]);
            test_insert_with_hint(m, ++m.begin(), items_[1]);
        }
    }

    void test_insert_single(ft::map<Key, T> &m, const ft::pair<const Key, T> &value)
    {
        std::cout << "insert(ft::make_pair";
        print_pair(value);
        std::cout << ") = ";
        ft::pair<typename ft::map<Key, T>::iterator, bool> ret = m.insert(value);
        std::cout << "Iter: ";
        print_pair(*ret.first);
        std::cout << ", Inserted: " << std::boolalpha << ret.second << std::endl;
    }

    void test_insert_with_hint(ft::map<Key, T> &m, typename ft::map<Key, T>::iterator pos, const ft::pair<const Key, T> &value)
    {
        std::cout << "insert(iter, ";
        print_pair(value);
        std::cout << ") = ";
        typename ft::map<Key, T>::iterator ret = m.insert(pos, value);
        std::cout << "Iter: ";
        print_pair(*ret);
        std::cout << std::endl;
        print_map(m);
    }

    void test_get_allocator()
    {
        print_test_case("map::get_allocator()");
        ft::map<Key, T, std::less<Key>, MyAllocator<ft::pair<const Key, T> > > m;
        std::cout << m.get_allocator().getNum() << std::endl;
    }
};

#endif /* MAPTESTER_HPP */
