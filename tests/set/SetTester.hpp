#ifndef SETTESTER_HPP
#define SETTESTER_HPP

#include "test.hpp"

template <class T>
class SetTester
{
public:
    SetTester() : items_(), items_len_(0) {}
    SetTester(T items[], size_t items_len)
        : items_(items), items_len_(items_len) {}
    ~SetTester() {}
    void test_all()
    {
        prepare_Set();

        test_constructor();
        test_operator_equal();

        // Capacity
        test_max_size();

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

        // Allocator
        test_get_allocator();

        // Non-member function
        test_relational_operator();
    }

private:
    T *items_;
    size_t items_len_;
    ft::set<T> orig_set_;

    void prepare_Set()
    {
        for (size_t i = 0; i < items_len_; i++)
        {
            orig_set_.insert(items_[i]);
        }
    }

    void print_set(ft::set<T> &s)
    {
        std::cout << std::boolalpha
                  << "size=" << s.size() << " empty=" << s.empty() << " items:";
        typename ft::set<T>::iterator iter = s.begin();
        for (size_t i = 0; i < s.size(); i++)
        {
            std::cout << "[" << i << "]=" << *iter;
            ++iter;
            if (i < s.size() - 1)
                std::cout << ", ";
        }
        std::cout << std::endl;
    }

    template <class Iter>
    void print_iter(ft::set<T> &s, Iter &iter)
    {
        std::cout << "Iter:";
        if (iter == s.end())
            std::cout << "end";
        else
            std::cout << *iter;
    }

    void test_constructor()
    {
        print_test_case("set() : default constructor");
        {
            ft::set<T> s;
            print_set(s);
        }
        print_test_case("set() : range constructor");
        {
            ft::set<T> dest(++orig_set_.begin(), --orig_set_.end());
            print_set(dest);
        }
        print_test_case("set() : copy constructor");
        {
            ft::set<T> dest(orig_set_);
            print_set(dest);
        }
    }

    void test_operator_equal()
    {
        print_test_case("set::operator=()");
        ft::set<T> s;
        s = orig_set_;
        print_set(s);
    }

    void test_max_size()
    {
        print_test_case("set::max_size()");
        ft::set<T> s;
        std::cout << s.max_size() << std::endl;
    }

    void test_insert()
    {
        print_test_case("set::insert() : single element");
        {
            ft::set<T> s;
            for (size_t i = 0; i < items_len_; i++)
            {
                test_insert_single(s, items_[i]);
            }
        }
        print_test_case("set::insert() : with hint(pos=end(), val=max)");
        {
            ft::set<T> s;
            for (size_t i = 0; i < items_len_; i++)
            {
                test_insert_with_hint(s, s.end(), items_[i]);
            }
        }
        print_test_case("set::insert() : with hint(pos=begin(), val=min)");
        {
            ft::set<T> s;
            for (size_t i = 0; i < items_len_; i++)
            {
                test_insert_with_hint(s, s.begin(), items_[items_len_ - i - 1]);
            }
        }
        print_test_case("set::insert() : with hint(pos=begin()+1, pos-1<val<pos)");
        {
            ft::set<T> s;
            s.insert(items_[0]);
            s.insert(items_[2]);
            test_insert_with_hint(s, ++s.begin(), items_[1]);
        }
        print_test_case("set::insert() : range");
        {
            ft::set<T> src(orig_set_), dest;
            dest.insert(src.begin(), src.end());
            print_set(dest);
        }
    }

    void test_insert_single(ft::set<T> &s, const T &value)
    {
        std::cout << "insert(" << value << ") = ";
        ft::pair<typename ft::set<T>::iterator, bool> ret = s.insert(value);
        print_iter(s, ret.first);
        std::cout << ", Inserted: " << std::boolalpha << ret.second << std::endl;
    }

    void test_insert_with_hint(ft::set<T> &s,
                               typename ft::set<T>::iterator pos,
                               const T &value)
    {
        std::cout << "insert(iter, " << value << ") = ";
        typename ft::set<T>::iterator ret = s.insert(pos, value);
        std::cout << "Iter: " << *ret << std::endl;
        print_set(s);
    }

    void test_erase()
    {
        print_test_case("set::erase() : iterator");
        {
            ft::set<T> s(orig_set_);
            typename ft::set<T>::iterator iter = s.begin();
            while (iter != s.end())
            {
                s.erase(iter);
                iter = s.begin();
            }
            print_set(s);
        }
        print_test_case("set::erase() : key");
        {
            ft::set<T> s(++orig_set_.begin(), --orig_set_.end());
            for (size_t i = 0; i < items_len_; i++)
            {
                std::cout << "erase(" << items_[i] << ") = "
                          << s.erase(items_[i]) << std::endl;
            }
        }
        print_test_case("set::erase() : range");
        {
            for (size_t start = 0; start < items_len_ + 1; start++)
            {
                for (size_t end = start; end < items_len_ + 1; end++)
                {
                    ft::set<T> s(items_, items_ + items_len_);
                    std::cout << "set(size=" << s.size() << ").erase(" << start << "-" << end << "): ";
                    typename ft::set<T>::iterator first = s.begin(), last = s.begin();
                    for (size_t i = 0; i < start; i++)
                    {
                        ++first;
                    }
                    for (size_t i = 0; i < end; i++)
                    {
                        ++last;
                    }
                    s.erase(first, last);
                    print_set(s);
                }
            }
        }
    }

    void test_clear()
    {
        print_test_case("set::clear()");
        ft::set<T> s(orig_set_);
        s.clear();
        print_set(s);
    }

    void test_swap()
    {
        print_test_case("set::swap()");
        {
            ft::set<T> lhs(orig_set_), rhs;
            lhs.swap(rhs);
            print_set(lhs);
            print_set(rhs);
        }
        print_test_case("ft::swap()");
        {
            ft::set<T> lhs(orig_set_), rhs;
            ft::swap(lhs, rhs);
            print_set(lhs);
            print_set(rhs);
        }
    }

    void test_key_comp()
    {
        print_test_case("set::key_comp()");
        ft::set<T> s;
        typename ft::set<T>::key_compare comp = s.key_comp();
        test_key_comp_sub(comp, items_[0], items_[1]);
        test_key_comp_sub(comp, items_[1], items_[1]);
        test_key_comp_sub(comp, items_[1], items_[0]);
    }

    void test_key_comp_sub(const typename ft::set<T>::key_compare &comp,
                           const T &lhs, const T &rhs)
    {
        std::cout << "key_comp(" << lhs << ", " << rhs << ") = "
                  << std::boolalpha << comp(lhs, rhs) << std::endl;
    }

    void test_value_comp()
    {
        print_test_case("set::value_comp()");
        ft::set<T> s;
        typename ft::set<T>::value_compare comp = s.value_comp();
        test_value_comp_sub(comp, items_[0], items_[1]);
        test_value_comp_sub(comp, items_[1], items_[1]);
        test_value_comp_sub(comp, items_[1], items_[0]);
    }

    void test_value_comp_sub(const typename ft::set<T>::value_compare &comp,
                             const typename ft::set<T>::value_type &lhs,
                             const typename ft::set<T>::value_type &rhs)
    {
        std::cout << "value_comp(" << lhs << ", " << rhs << ") = "
                  << std::boolalpha << comp(lhs, rhs) << std::endl;
    }

    void test_find()
    {
        print_test_case("set::find()");
        ft::set<T> s(++orig_set_.begin(), --orig_set_.end());
        for (size_t i = 0; i < items_len_; i++)
        {
            std::cout << "find(" << items_[i] << ") = ";
            typename ft::set<T>::iterator iter = s.find(items_[i]);
            print_iter(s, iter);
            std::cout << std::endl;
        }
    }

    void test_count()
    {
        print_test_case("set::count()");
        ft::set<T> s(++orig_set_.begin(), --orig_set_.end());
        for (size_t i = 0; i < items_len_; i++)
        {
            std::cout << "count(" << items_[i] << ") = "
                      << s.count(items_[i]) << std::endl;
        }
    }

    void test_lower_bound()
    {
        print_test_case("set::lower_bound()");
        ft::set<T> s(++orig_set_.begin(), --orig_set_.end());
        for (size_t i = 0; i < items_len_; i++)
        {
            std::cout << "lower_bound(" << items_[i] << ") = ";
            typename ft::set<T>::iterator iter = s.lower_bound(items_[i]);
            print_iter(s, iter);
            std::cout << std::endl;
        }
    }

    void test_upper_bound()
    {
        print_test_case("set::upper_bound()");
        ft::set<T> s(++orig_set_.begin(), --orig_set_.end());
        for (size_t i = 0; i < items_len_; i++)
        {
            std::cout << "upper_bound(" << items_[i] << ") = ";
            typename ft::set<T>::iterator iter = s.upper_bound(items_[i]);
            print_iter(s, iter);
            std::cout << std::endl;
        }
    }

    void test_equal_range()
    {
        print_test_case("set::equal_range()");
        ft::set<T> s(++orig_set_.begin(), --orig_set_.end());
        for (size_t i = 0; i < items_len_; i++)
        {
            T key = items_[i];
            std::cout << "equal_range(" << key << ") = pair(";
            ft::pair<typename ft::set<T>::iterator, typename ft::set<T>::iterator> ret = s.equal_range(key);
            print_iter(s, ret.first);
            std::cout << ", ";
            print_iter(s, ret.second);
            std::cout << ")" << std::endl;
        }
    }

    void test_get_allocator()
    {
        print_test_case("set::get_allocator()");
        ft::set<T, std::less<T>, MyAllocator<T> > s;
        std::cout << s.get_allocator().getNum() << std::endl;
    }

    void test_relational_operator()
    {
        print_test_case("map::operator==, !=, <, <=, >, >=");
        ft::set<T> empty1;
        ft::set<T> empty2;
        ft::set<T> size_small1(orig_set_.begin(), --orig_set_.end());
        ft::set<T> size_small2(size_small1);
        ft::set<T> size_large(orig_set_);

        std::cout << std::boolalpha
                  << "empty == empty     : " << (empty1 == empty2) << std::endl
                  << "empty == small     : " << (empty1 == size_small1) << std::endl
                  << "small == small     : " << (size_small1 == size_small2) << std::endl;
        std::cout << std::boolalpha
                  << "empty != empty     : " << (empty1 != empty2) << std::endl
                  << "empty != small     : " << (empty1 != size_small1) << std::endl
                  << "small != small     : " << (size_small1 != size_small2) << std::endl;
        std::cout << std::boolalpha
                  << "empty    <  empty     : " << (empty1 < empty2) << std::endl
                  << "empty    <  small     : " << (empty1 < size_small1) << std::endl
                  << "small    <  empty     : " << (size_small1 < empty1) << std::endl
                  << "small    <  small     : " << (size_small1 < size_small2) << std::endl
                  << "large    <  small     : " << (size_large < size_small1) << std::endl
                  << "small    <  large     : " << (size_small1 < size_large) << std::endl;
        std::cout << std::boolalpha
                  << "empty    <= empty     : " << (empty1 <= empty2) << std::endl
                  << "empty    <= small     : " << (empty1 <= size_small1) << std::endl
                  << "small    <= empty     : " << (size_small1 <= empty1) << std::endl
                  << "small    <= small     : " << (size_small1 <= size_small2) << std::endl
                  << "large    <= small     : " << (size_large <= size_small1) << std::endl
                  << "small    <= large     : " << (size_small1 <= size_large) << std::endl;
        std::cout << std::boolalpha
                  << "empty    >  empty     : " << (empty1 > empty2) << std::endl
                  << "empty    >  small     : " << (empty1 > size_small1) << std::endl
                  << "small    >  empty     : " << (size_small1 > empty1) << std::endl
                  << "small    >  small     : " << (size_small1 > size_small2) << std::endl
                  << "large    >  small     : " << (size_large > size_small1) << std::endl
                  << "small    >  large     : " << (size_small1 > size_large) << std::endl;
        std::cout << std::boolalpha
                  << "empty    >= empty     : " << (empty1 >= empty2) << std::endl
                  << "empty    >= small     : " << (empty1 >= size_small1) << std::endl
                  << "small    >= empty     : " << (size_small1 >= empty1) << std::endl
                  << "small    >= small     : " << (size_small1 >= size_small2) << std::endl
                  << "large    >= small     : " << (size_large >= size_small1) << std::endl
                  << "small    >= large     : " << (size_small1 >= size_large) << std::endl;
    }
};

#endif /* SETTESTER_HPP */
