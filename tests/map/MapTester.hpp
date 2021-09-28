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

        // Observers
        test_key_comp();
        test_value_comp();

        // Operations
        test_find();
        test_lower_bound();
        test_upper_bound();

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

    template <class Iter>
    void print_iter(ft::map<Key, T> &m, Iter &iter)
    {
        std::cout << "Iter:";
        if (iter == m.end())
            std::cout << "end";
        else
            print_pair(*iter);
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
        print_test_case("map::insert() : range");
        {
            ft::map<Key, T> src, dest;
            for (size_t i = 0; i < items_len_; i++)
            {
                src.insert(items_[i]);
            }
            dest.insert(src.begin(), src.end());
            print_map(dest);
        }
    }

    void test_insert_single(ft::map<Key, T> &m, const ft::pair<const Key, T> &value)
    {
        std::cout << "insert(ft::make_pair";
        print_pair(value);
        std::cout << ") = ";
        ft::pair<typename ft::map<Key, T>::iterator, bool> ret = m.insert(value);
        print_iter(m, ret.first);
        std::cout << ", Inserted: " << std::boolalpha << ret.second << std::endl;
    }

    void test_insert_with_hint(ft::map<Key, T> &m,
                               typename ft::map<Key, T>::iterator pos,
                               const ft::pair<const Key, T> &value)
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

    void test_key_comp()
    {
        print_test_case("map::key_comp()");
        ft::map<Key, T> m;
        typename ft::map<Key, T>::key_compare comp = m.key_comp();
        test_key_comp_sub(comp, items_[0].first, items_[1].first);
        test_key_comp_sub(comp, items_[1].first, items_[1].first);
        test_key_comp_sub(comp, items_[1].first, items_[0].first);
    }

    void test_key_comp_sub(const typename ft::map<Key, T>::key_compare &comp,
                           const Key &lhs, const Key &rhs)
    {
        std::cout << "key_comp(" << lhs << ", " << rhs << ") = "
                  << std::boolalpha << comp(lhs, rhs) << std::endl;
    }

    void test_value_comp()
    {
        print_test_case("map::value_comp()");
        ft::map<Key, T> m;
        typename ft::map<Key, T>::value_compare comp = m.value_comp();
        test_value_comp_sub(comp, items_[0], items_[1]);
        test_value_comp_sub(comp, items_[1], items_[1]);
        test_value_comp_sub(comp, items_[1], items_[0]);
    }

    void test_value_comp_sub(const typename ft::map<Key, T>::value_compare &comp,
                             const typename ft::map<Key, T>::value_type &lhs,
                             const typename ft::map<Key, T>::value_type &rhs)
    {
        std::cout << "value_comp(";
        print_pair(lhs);
        std::cout << ", ";
        print_pair(rhs);
        std::cout << ") = "
                  << std::boolalpha << comp(lhs, rhs) << std::endl;
    }

    void test_find()
    {
        print_test_case("map::find()");
        ft::map<Key, T> m;
        for (size_t i = 1; i < items_len_ - 1; i++)
        {
            m.insert(items_[i]);
        }
        for (size_t i = 0; i < items_len_; i++)
        {
            std::cout << "find(" << items_[i].first << ") = ";
            typename ft::map<Key, T>::iterator iter = m.find(items_[i].first);
            print_iter(m, iter);
            std::cout << std::endl;
        }
    }

    void test_lower_bound()
    {
        print_test_case("map::lower_bound()");
        ft::map<Key, T> m;
        for (size_t i = 1; i < items_len_ - 1; i++)
        {
            m.insert(items_[i]);
        }
        for (size_t i = 0; i < items_len_; i++)
        {
            std::cout << "lower_bound(" << items_[i].first << ") = ";
            typename ft::map<Key, T>::iterator iter = m.lower_bound(items_[i].first);
            print_iter(m, iter);
            std::cout << std::endl;
        }
    }

    void test_upper_bound()
    {
        print_test_case("map::upper_bound()");
        ft::map<Key, T> m;
        for (size_t i = 1; i < items_len_ - 1; i++)
        {
            m.insert(items_[i]);
        }
        for (size_t i = 0; i < items_len_; i++)
        {
            std::cout << "upper_bound(" << items_[i].first << ") = ";
            typename ft::map<Key, T>::iterator iter = m.upper_bound(items_[i].first);
            print_iter(m, iter);
            std::cout << std::endl;
        }
    }

    void test_get_allocator()
    {
        print_test_case("map::get_allocator()");
        ft::map<Key, T, std::less<Key>, MyAllocator<ft::pair<const Key, T> > > m;
        std::cout << m.get_allocator().getNum() << std::endl;
    }
};

#endif /* MAPTESTER_HPP */
