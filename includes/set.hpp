#ifndef SET_HPP
#define SET_HPP

#include <algorithm>
#include "iterator.hpp"
#include "tree_.hpp"

namespace ft
{
    template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
    class set
    {
    public:
        // Member types
        typedef T key_type;
        typedef T value_type;
        typedef Compare key_compare;
        typedef Compare value_compare;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;

    private:
        typedef rb_tree_<key_type, value_type, value_compare, allocator_type> tree_type;

    public:
        typedef typename tree_type::iterator iterator;
        typedef typename tree_type::const_iterator const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef typename iterator_traits<iterator>::difference_type difference_type;
        typedef size_t size_type;

        // Member functions
        explicit set(const key_compare &comp = key_compare(),
                     const allocator_type &alloc = allocator_type())
            : tree_(comp, alloc), compare_(comp) {}
        template <class InputIterator>
        set(InputIterator first, InputIterator last,
            const key_compare &comp = key_compare(),
            const allocator_type &alloc = allocator_type())
            : tree_(comp, alloc), compare_(comp)
        {
            insert(first, last);
        }
        set(const set &x) : tree_(x.tree_)
        {
            insert(x.begin(), x.end());
        }
        ~set() {}
        set &operator=(const set &x)
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
            return reverse_iterator(end());
        }
        reverse_iterator rend()
        {
            return reverse_iterator(begin());
        }
        const_reverse_iterator rend() const
        {
            return reverse_iterator(begin());
        }

        // Capacity
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
        size_type erase(const value_type &val)
        {
            return tree_.erase(val);
        }
        void erase(iterator first, iterator last)
        {
            tree_.erase(first, last);
        }
        void swap(set &x)
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
            return compare_;
        }
        value_compare value_comp() const
        {
            return compare_;
        }

        // Operations
        iterator find(const value_type &val) const
        {
            return tree_.find(val);
        }
        size_type count(const value_type &val) const
        {
            return tree_.count(val);
        }
        iterator lower_bound(const value_type &val) const
        {
            return tree_.lower_bound(val);
        }
        iterator upper_bound(const value_type &val) const
        {
            return tree_.upper_bound(val);
        }
        pair<iterator, iterator> equal_range(const value_type &val) const
        {
            return tree_.equal_range(val);
        }

        // Allocator
        allocator_type get_allocator() const
        {
            return allocator_type(tree_.get_allocator());
        }

    private:
        tree_type tree_;
        value_compare compare_;
    };

    // Non-member functions
    template <class T, class Compare, class Alloc>
    bool operator==(const set<T, Compare, Alloc> &lhs,
                    const set<T, Compare, Alloc> &rhs)
    {
        return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }
    template <class T, class Compare, class Alloc>
    bool operator!=(const set<T, Compare, Alloc> &lhs,
                    const set<T, Compare, Alloc> &rhs)
    {
        return !(lhs == rhs);
    }
    template <class T, class Compare, class Alloc>
    bool operator<(const set<T, Compare, Alloc> &lhs,
                   const set<T, Compare, Alloc> &rhs)
    {
        return ft::lexicographical_compare(
            lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
    template <class T, class Compare, class Alloc>
    bool operator<=(const set<T, Compare, Alloc> &lhs,
                    const set<T, Compare, Alloc> &rhs)
    {
        return !(rhs < lhs);
    }
    template <class T, class Compare, class Alloc>
    bool operator>(const set<T, Compare, Alloc> &lhs,
                   const set<T, Compare, Alloc> &rhs)
    {
        return rhs < lhs;
    }
    template <class T, class Compare, class Alloc>
    bool operator>=(const set<T, Compare, Alloc> &lhs,
                    const set<T, Compare, Alloc> &rhs)
    {
        return !(lhs < rhs);
    }

    template <class T, class Compare, class Alloc>
    void swap(set<T, Compare, Alloc> &x, set<T, Compare, Alloc> &y)
    {
        x.swap(y);
    }

} /* namespace ft */

#endif /* SET_HPP */
