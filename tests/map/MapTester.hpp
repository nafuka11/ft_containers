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
                  << "size=" << m.size() << " empty=" << m.empty() << std::endl;
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
        print_test_case("map::insert()");
        ft::map<Key, T> m;
        for (size_t i = 0; i < items_len_; i++)
        {
            test_insert_sub(m, items_[i]);
        }
        test_insert_sub(m, ft::make_pair(items_[0].first, items_[1].second));
    }

    void test_insert_sub(ft::map<Key, T> &m, const ft::pair<const Key, T> &value)
    {
        std::cout << "insert(ft::make_pair";
        print_pair(value);
        std::cout << ") = ";
        ft::pair<typename ft::map<Key, T>::iterator, bool> ret = m.insert(value);
        std::cout << "Iter: ";
        print_pair(*ret.first);
        std::cout << ", Inserted: " << std::boolalpha << ret.second << std::endl;
    }

    void test_get_allocator()
    {
        print_test_case("map::get_allocator()");
        ft::map<Key, T, std::less<Key>, MyAllocator<ft::pair<const Key, T> > > m;
        std::cout << m.get_allocator().getNum() << std::endl;
    }
};

#endif /* MAPTESTER_HPP */
