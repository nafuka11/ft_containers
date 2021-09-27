#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include "iterator.hpp"
#include "tree_.hpp"
#include "utility.hpp"

namespace ft
{
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
        typedef Allocator allocator_type;

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

    private:
        typedef rb_tree_<value_type, value_compare, allocator_type> tree_type;

    public:
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef typename tree_type::iterator iterator;
        typedef typename tree_type::iterator const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef typename allocator_type::difference_type difference_type;
        typedef typename allocator_type::size_type size_type;

    public:
        // Member functions
        // constructor
        explicit map(const key_compare &comp = key_compare(),
                     const allocator_type &alloc = allocator_type())
            : key_comp_(comp), value_comp_(value_compare(comp)),
              tree_(value_comp_, alloc) {}
        // template <class InputIterator>
        // map(InputIterator first, InputIterator last,
        //     const key_compare &comp = key_compare(),
        //     const allocator_type &alloc = allocator_type())
        // {}
        // map(const map &x) {}
        // destructor
        ~map() {}
        // // operator=
        // map &operator=(const map &x) {}

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

        // reverse_iterator rbegin();
        // const_reverse_iterator rbegin() const;

        // reverse_iterator rend();
        // const_reverse_iterator rend() const;

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

        // // Element access
        // mapped_type &operator[](const key_type &k);

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

        // void erase(iterator position);
        // size_type erase(const key_type &k);
        // void erase(iterator first, iterator last);

        // void swap(map &x);
        // void clear();

        // // Observers
        // key_compare key_comp() const;
        // value_compare value_comp() const;

        // // Operations
        // iterator find(const key_type &k);
        // const_iterator find(const key_type &k) const;

        // size_type count(const key_type &k) const;

        // iterator lower_bound(const key_type &k);
        // const_iterator lower_bound(const key_type &k) const;

        // iterator upper_bound(const key_type &k);
        // const_iterator upper_bound(const key_type &k) const;

        // pair<const_iterator, const_iterator> equal_range(const key_type &k) const;
        // pair<iterator, iterator> equal_range(const key_type &k);

        allocator_type get_allocator() const
        {
            return allocator_type(tree_.get_allocator());
        }

    private:
        key_compare key_comp_;
        value_compare value_comp_;
        tree_type tree_;
    };
} /* namespace ft */

#endif /* MAP_HPP */
