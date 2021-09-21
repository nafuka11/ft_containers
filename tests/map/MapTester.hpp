#ifndef MAPTESTER_HPP
#define MAPTESTER_HPP

#include "common.hpp"

template <class Key, class T>
class MapTester
{
public:
    MapTester() : items_(), items_len_(0) {}
    MapTester(ft::pair<const Key, T> *items, size_t items_len)
        : items_(items), items_len_(items_len) {}
    ~MapTester() {}
    void test_all()
    {
        test_constructor();
    }

private:
    ft::pair<const Key, T> *items_;
    size_t items_len_;

    void print_map(ft::map<Key, T> &m)
    {
        std::cout << std::boolalpha
                  << "size=" << m.size() << " empty=" << m.empty() << std::endl;
    }

    void test_constructor()
    {
        print_test_case("map()");
        ft::map<Key, T> m;
        print_map(m);
    }
};

#endif /* MAPTESTER_HPP */
