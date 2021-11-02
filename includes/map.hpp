#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include "algorithm.hpp"
#include "iterator.hpp"
#include "tree_.hpp"
#include "utility.hpp"

namespace ft
{
    template <class Key, class Value, class Compare>
    class map_value_compare_ : private Compare
    {
    public:
        map_value_compare_() : Compare() {}
        map_value_compare_(Compare c) : Compare(c) {}

        bool operator()(const Value &lhs, const Value &rhs) const
        {
            return static_cast<const Compare &>(*this)(lhs.first, rhs.first);
        }
        bool operator()(const Value &lhs, const Key &rhs) const
        {
            return static_cast<const Compare &>(*this)(lhs.first, rhs);
        }
        bool operator()(const Key &lhs, const Value &rhs) const
        {
            return static_cast<const Compare &>(*this)(lhs, rhs.first);
        }
    };

    template <class Key, class T, class Compare = std::less<Key>,
              class Allocator = std::allocator<pair<const Key, T> > >
    class map
    {
    public:
        // Member types
        typedef Key key_type;
        typedef T mapped_type;
        typedef pair<const key_type, mapped_type> value_type;
        typedef Compare key_compare;

        class value_compare : std::binary_function<value_type, value_type, bool>
        {
        public:
            Compare comp;
            value_compare(Compare c) : comp(c) {}

            typedef bool result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;
            bool operator()(const value_type &lhs, const value_type &rhs) const
            {
                return comp(lhs.first, rhs.first);
            }
        };

        typedef Allocator allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;

    private:
        typedef map_value_compare_<key_type, value_type, key_compare> tree_compare;
        typedef rb_tree_<key_type, value_type, tree_compare, allocator_type> tree_type;

    public:
        typedef typename tree_type::iterator iterator;
        typedef typename tree_type::const_iterator const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef typename iterator_traits<iterator>::difference_type difference_type;
        typedef size_t size_type;

    public:
        // Member functions
        // constructor
        explicit map(const key_compare &comp = key_compare(),
                     const allocator_type &alloc = allocator_type())
            : key_comp_(comp), value_comp_(value_compare(comp)),
              tree_(tree_compare(comp), alloc) {}

        template <class InputIterator>
        map(InputIterator first, InputIterator last,
            const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type())
            : key_comp_(comp), value_comp_(value_compare(comp)),
              tree_(tree_compare(comp), alloc)
        {
            insert(first, last);
        }

        map(const map &x) : key_comp_(x.key_comp_), value_comp_(x.value_comp_),
                            tree_(x.tree_)
        {
            insert(x.begin(), x.end());
        }
        // destructor
        ~map() {}
        // operator=
        map &operator=(const map &x)
        {
            tree_ = x.tree_;
            return *this;
        }

        // Iterators
        iterator begin()
        {
            return tree_.begin();
        }
        const_iterator begin() const
        {
            return tree_.begin();
        }

        iterator end()
        {
            return tree_.end();
        }
        const_iterator end() const
        {
            return tree_.end();
        }

        reverse_iterator rbegin()
        {
            return reverse_iterator(end());
        }
        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(end());
        }

        reverse_iterator rend()
        {
            return reverse_iterator(begin());
        }
        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(begin());
        }

        // // Capacity
        bool empty() const
        {
            return tree_.size() == 0;
        }
        size_type size() const
        {
            return tree_.size();
        }
        size_type max_size() const
        {
            return tree_.max_size();
        }

        // Element access
        mapped_type &operator[](const key_type &k)
        {
            iterator iter = find(k);
            if (iter == end())
                iter = insert(value_type(k, mapped_type())).first;
            return iter->second;
        }

        // Modifiers
        pair<iterator, bool> insert(const value_type &val)
        {
            return tree_.insert(val);
        }
        iterator insert(iterator position, const value_type &val)
        {
            return tree_.insert(position, val);
        }
        template <class InputIterator>
        void insert(InputIterator first, InputIterator last)
        {
            for (; first != last; ++first)
            {
                tree_.insert(end(), *first);
            }
        }

        void erase(iterator position)
        {
            tree_.erase(position);
        }
        size_type erase(const key_type &k)
        {
            return tree_.erase(k);
        }
        void erase(iterator first, iterator last)
        {
            tree_.erase(first, last);
        }

        void swap(map &x)
        {
            tree_.swap(x.tree_);
        }

        void clear()
        {
            tree_.clear();
        }

        // Observers
        key_compare key_comp() const
        {
            return key_comp_;
        }
        value_compare value_comp() const
        {
            return value_comp_;
        }

        // Operations
        iterator find(const key_type &k)
        {
            return tree_.find(k);
        }
        const_iterator find(const key_type &k) const
        {
            return tree_.find(k);
        }

        size_type count(const key_type &k) const
        {
            return tree_.count(k);
        }

        iterator lower_bound(const key_type &k)
        {
            return tree_.lower_bound(k);
        }
        const_iterator lower_bound(const key_type &k) const
        {
            return tree_.lower_bound(k);
        }

        iterator upper_bound(const key_type &k)
        {
            return tree_.upper_bound(k);
        }
        const_iterator upper_bound(const key_type &k) const
        {
            return tree_.upper_bound(k);
        }

        pair<const_iterator, const_iterator> equal_range(const key_type &k) const
        {
            return tree_.equal_range(k);
        }
        pair<iterator, iterator> equal_range(const key_type &k)
        {
            return tree_.equal_range(k);
        }

        // Allocator
        allocator_type get_allocator() const
        {
            return allocator_type(tree_.get_allocator());
        }

    private:
        key_compare key_comp_;
        value_compare value_comp_;
        tree_type tree_;
    };

    // Non-member functions
    template <class Key, class T, class Compare, class Alloc>
    bool operator==(const ft::map<Key, T, Compare, Alloc> &lhs,
                    const ft::map<Key, T, Compare, Alloc> &rhs)
    {
        return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator!=(const ft::map<Key, T, Compare, Alloc> &lhs,
                    const ft::map<Key, T, Compare, Alloc> &rhs)
    {
        return !(lhs == rhs);
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator<(const ft::map<Key, T, Compare, Alloc> &lhs,
                   const ft::map<Key, T, Compare, Alloc> &rhs)
    {
        return ft::lexicographical_compare(
            lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator<=(const ft::map<Key, T, Compare, Alloc> &lhs,
                    const ft::map<Key, T, Compare, Alloc> &rhs)
    {
        return !(rhs < lhs);
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator>(const ft::map<Key, T, Compare, Alloc> &lhs,
                   const ft::map<Key, T, Compare, Alloc> &rhs)
    {
        return rhs < lhs;
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator>=(const ft::map<Key, T, Compare, Alloc> &lhs,
                    const ft::map<Key, T, Compare, Alloc> &rhs)
    {
        return !(lhs < rhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    void swap(ft::map<Key, T, Compare, Alloc> &x,
              ft::map<Key, T, Compare, Alloc> &y)
    {
        x.swap(y);
    }

} /* namespace ft */

#endif /* MAP_HPP */
