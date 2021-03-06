#ifndef MAPTESTER_HPP
#define MAPTESTER_HPP

#include "test.hpp"

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
        prepare_map();

        test_constructor();
        test_operator_equal();

        // Capacity
        test_max_size();

        // Element access
        test_subscript_operator();

        // Modifiers
        test_insert();
        test_erase();
        test_clear();
        test_swap();

        // Observers
        test_key_comp();
        test_value_comp();

        // Operations
        test_find();
        test_count();
        test_lower_bound();
        test_upper_bound();
        test_equal_range();

        test_get_allocator();

        // Non-member function
        test_relational_operator();
    }

private:
    ft::pair<const Key, T> *items_;
    size_t items_len_;
    ft::map<Key, T> orig_map_;

    void prepare_map()
    {
        for (size_t i = 0; i < items_len_; i++)
        {
            orig_map_.insert(items_[i]);
        }
    }

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
        print_test_case("map() : default constructor");
        {
            ft::map<Key, T> m;
            print_map(m);
        }
        print_test_case("map() : range constructor");
        {
            ft::map<Key, T> dest(++orig_map_.begin(), --orig_map_.end());
            print_map(dest);
        }
        print_test_case("map() : copy constructor");
        {
            ft::map<Key, T> dest(orig_map_);
            print_map(dest);
        }
    }

    void test_operator_equal()
    {
        print_test_case("map::operator=()");
        ft::map<Key, T> m;
        m = orig_map_;
        print_map(m);
    }

    void test_max_size()
    {
        print_test_case("map::max_size()");
        ft::map<Key, T> m;
        std::cout << m.max_size() << std::endl;
    }

    void test_subscript_operator()
    {
        print_test_case("map::operator[]");
        ft::map<Key, T> m(++orig_map_.begin(), --orig_map_.end());
        for (size_t i = 0; i < items_len_ / 2 + 1; i++)
        {
            std::cout << "m[" << items_[i].first << "] = "
                      << m[items_[i].first] << std::endl;
        }
        for (size_t i = items_len_ / 2 + 1; i < items_len_; i++)
        {
            m[items_[i].first] = items_[items_len_ / 2].second;
            std::cout << "m[" << items_[i].first << "] = "
                      << m[items_[i].first] << std::endl;
        }
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
            ft::map<Key, T> src(orig_map_), dest;
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

    void test_erase()
    {
        print_test_case("map::erase() : iterator");
        {
            ft::map<Key, T> m(orig_map_);
            typename ft::map<Key, T>::iterator iter = m.begin();
            while (iter != m.end())
            {
                m.erase(iter);
                iter = m.begin();
            }
            print_map(m);
        }
        print_test_case("map::erase() : key");
        {
            ft::map<Key, T> m(++orig_map_.begin(), --orig_map_.end());
            for (size_t i = 0; i < items_len_; i++)
            {
                std::cout << "erase(" << items_[i].first << ") = "
                          << m.erase(items_[i].first) << std::endl;
            }
        }
        print_test_case("map::erase() : range");
        {
            for (size_t start = 0; start < items_len_ + 1; start++)
            {
                for (size_t end = start; end < items_len_ + 1; end++)
                {
                    ft::map<Key, T> m(items_, items_ + items_len_);
                    std::cout << "m(size=" << m.size() << ").erase(" << start << "-" << end << "): ";
                    typename ft::map<Key, T>::iterator first = m.begin(), last = m.begin();
                    for (size_t i = 0; i < start; i++)
                    {
                        ++first;
                    }
                    for (size_t i = 0; i < end; i++)
                    {
                        ++last;
                    }
                    m.erase(first, last);
                    print_map(m);
                }
            }
        }
    }

    void test_clear()
    {
        print_test_case("map::clear()");
        ft::map<Key, T> m(orig_map_);
        m.clear();
        print_map(m);
    }

    void test_swap()
    {
        print_test_case("map::swap()");
        {
            ft::map<Key, T> lhs(orig_map_), rhs;
            lhs.swap(rhs);
            print_map(lhs);
            print_map(rhs);
        }
        print_test_case("ft::swap()");
        {
            ft::map<Key, T> lhs(orig_map_), rhs;
            ft::swap(lhs, rhs);
            print_map(lhs);
            print_map(rhs);
        }
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
        ft::map<Key, T> m(++orig_map_.begin(), --orig_map_.end());
        for (size_t i = 0; i < items_len_; i++)
        {
            std::cout << "find(" << items_[i].first << ") = ";
            typename ft::map<Key, T>::iterator iter = m.find(items_[i].first);
            print_iter(m, iter);
            std::cout << std::endl;
        }
    }

    void test_count()
    {
        print_test_case("map::count()");
        ft::map<Key, T> m(++orig_map_.begin(), --orig_map_.end());
        for (size_t i = 0; i < items_len_; i++)
        {
            std::cout << "count(" << items_[i].first << ") = "
                      << m.count(items_[i].first) << std::endl;
        }
    }

    void test_lower_bound()
    {
        print_test_case("map::lower_bound()");
        ft::map<Key, T> m(++orig_map_.begin(), --orig_map_.end());
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
        ft::map<Key, T> m(++orig_map_.begin(), --orig_map_.end());
        for (size_t i = 0; i < items_len_; i++)
        {
            std::cout << "upper_bound(" << items_[i].first << ") = ";
            typename ft::map<Key, T>::iterator iter = m.upper_bound(items_[i].first);
            print_iter(m, iter);
            std::cout << std::endl;
        }
    }

    void test_equal_range()
    {
        print_test_case("map::equal_range()");
        ft::map<Key, T> m(++orig_map_.begin(), --orig_map_.end());
        for (size_t i = 0; i < items_len_; i++)
        {
            Key key = items_[i].first;
            std::cout << "equal_range(" << key << ") = pair(";
            ft::pair<typename ft::map<Key, T>::iterator, typename ft::map<Key, T>::iterator> ret = m.equal_range(key);
            print_iter(m, ret.first);
            std::cout << ", ";
            print_iter(m, ret.second);
            std::cout << ")" << std::endl;
        }
    }

    void test_get_allocator()
    {
        print_test_case("map::get_allocator()");
        ft::map<Key, T, std::less<Key>, MyAllocator<ft::pair<const Key, T> > > m;
        std::cout << m.get_allocator().getNum() << std::endl;
    }

    void test_relational_operator()
    {
        print_test_case("map::operator==, !=, <, <=, >, >=");
        ft::map<Key, T> empty1;
        ft::map<Key, T> empty2;
        ft::map<Key, T> size_small1(orig_map_.begin(), --orig_map_.end());
        ft::map<Key, T> size_small2(size_small1);
        ft::map<Key, T> front_diff(size_small1);
        ft::map<Key, T> back_diff(size_small1);
        ft::map<Key, T> size_large(orig_map_);
        front_diff.begin()->second = items_[items_len_ - 1].second;
        (--back_diff.end())->second = items_[items_len_ - 1].second;

        std::cout << std::boolalpha
                  << "empty == empty     : " << (empty1 == empty2) << std::endl
                  << "empty == small     : " << (empty1 == size_small1) << std::endl
                  << "small == small     : " << (size_small1 == size_small2) << std::endl
                  << "small == frontDiff : " << (size_small1 == front_diff) << std::endl
                  << "small == backDiff  : " << (size_small2 == back_diff) << std::endl;
        std::cout << std::boolalpha
                  << "empty != empty     : " << (empty1 != empty2) << std::endl
                  << "empty != small     : " << (empty1 != size_small1) << std::endl
                  << "small != small     : " << (size_small1 != size_small2) << std::endl
                  << "small != frontDiff : " << (size_small1 != front_diff) << std::endl
                  << "small != backDiff  : " << (size_small2 != back_diff) << std::endl;
        std::cout << std::boolalpha
                  << "empty    <  empty     : " << (empty1 < empty2) << std::endl
                  << "empty    <  small     : " << (empty1 < size_small1) << std::endl
                  << "small    <  empty     : " << (size_small1 < empty1) << std::endl
                  << "small    <  small     : " << (size_small1 < size_small2) << std::endl
                  << "large    <  small     : " << (size_large < size_small1) << std::endl
                  << "small    <  large     : " << (size_small1 < size_large) << std::endl
                  << "small    <  frontDiff : " << (size_small1 < front_diff) << std::endl
                  << "frontDiff<  small     : " << (front_diff < size_small1) << std::endl
                  << "small    <  backDiff  : " << (size_small2 < back_diff) << std::endl
                  << "backDiff <  small     : " << (back_diff < back_diff) << std::endl;
        std::cout << std::boolalpha
                  << "empty    <= empty     : " << (empty1 <= empty2) << std::endl
                  << "empty    <= small     : " << (empty1 <= size_small1) << std::endl
                  << "small    <= empty     : " << (size_small1 <= empty1) << std::endl
                  << "small    <= small     : " << (size_small1 <= size_small2) << std::endl
                  << "large    <= small     : " << (size_large <= size_small1) << std::endl
                  << "small    <= large     : " << (size_small1 <= size_large) << std::endl
                  << "small    <= frontDiff : " << (size_small1 <= front_diff) << std::endl
                  << "frontDiff<= small     : " << (front_diff <= size_small1) << std::endl
                  << "small    <= backDiff  : " << (size_small2 <= back_diff) << std::endl
                  << "backDiff <= small     : " << (back_diff <= back_diff) << std::endl;
        std::cout << std::boolalpha
                  << "empty    >  empty     : " << (empty1 > empty2) << std::endl
                  << "empty    >  small     : " << (empty1 > size_small1) << std::endl
                  << "small    >  empty     : " << (size_small1 > empty1) << std::endl
                  << "small    >  small     : " << (size_small1 > size_small2) << std::endl
                  << "large    >  small     : " << (size_large > size_small1) << std::endl
                  << "small    >  large     : " << (size_small1 > size_large) << std::endl
                  << "small    >  frontDiff : " << (size_small1 > front_diff) << std::endl
                  << "frontDiff>  small     : " << (front_diff > size_small1) << std::endl
                  << "small    >  backDiff  : " << (size_small2 > back_diff) << std::endl
                  << "backDiff >  small     : " << (back_diff > back_diff) << std::endl;
        std::cout << std::boolalpha
                  << "empty    >= empty     : " << (empty1 >= empty2) << std::endl
                  << "empty    >= small     : " << (empty1 >= size_small1) << std::endl
                  << "small    >= empty     : " << (size_small1 >= empty1) << std::endl
                  << "small    >= small     : " << (size_small1 >= size_small2) << std::endl
                  << "large    >= small     : " << (size_large >= size_small1) << std::endl
                  << "small    >= large     : " << (size_small1 >= size_large) << std::endl
                  << "small    >= frontDiff : " << (size_small1 >= front_diff) << std::endl
                  << "frontDiff>= small     : " << (front_diff >= size_small1) << std::endl
                  << "small    >= backDiff  : " << (size_small2 >= back_diff) << std::endl
                  << "backDiff >= small     : " << (back_diff >= back_diff) << std::endl;
    }
};

#endif /* MAPTESTER_HPP */
