#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "iterator.hpp"
#include "type_traits.hpp"

namespace ft
{
    template <class T>
    class vector_iterator_ : public std::iterator<std::random_access_iterator_tag, T>
    {
        public:
            typedef T iterator_type;
            typedef typename iterator_traits<T>::iterator_category iterator_category;
            typedef typename iterator_traits<T>::value_type value_type;
            typedef typename iterator_traits<T>::difference_type difference_type;
            typedef typename iterator_traits<T>::pointer pointer;
            typedef typename iterator_traits<T>::reference reference;

            // Member functions
            // constructor
            vector_iterator_() : current(NULL) {}
            explicit vector_iterator_(iterator_type ptr) : current(ptr) {}
            // copy constructor
            template <class Iter>
            vector_iterator_(const vector_iterator_<Iter> &other)
            {
                *this = other;
            }
            // destructor
            ~vector_iterator_() {}
            // assignment operator
            template <class Iter>
            vector_iterator_ &operator=(const vector_iterator_<Iter> &other)
            {
                current = other.base();
                return *this;
            }

            iterator_type base() const
            {
                return current;
            }
            // dereference operator
            reference operator*() const
            {
                return *current;
            }
            pointer operator->() const
            {
                return current;
            }
            // prefix/postfix increment
            vector_iterator_ &operator++()
            {
                current++;
                return *this;
            }
            vector_iterator_ operator++(int)
            {
                vector_iterator_ tmp = *this;
                current++;
                return tmp;
            }
            // prefix/postfix decrement
            vector_iterator_ &operator--()
            {
                current--;
                return *this;
            }
            vector_iterator_ operator--(int)
            {
                vector_iterator_ tmp = *this;
                current--;
                return tmp;
            }
            // arithmetic operators
            vector_iterator_ operator+(difference_type n) const
            {
                return vector_iterator_(current + n);
            }
            vector_iterator_ operator-(difference_type n) const
            {
                return vector_iterator_(current - n);
            }
            // compound assignment operators
            vector_iterator_ &operator+=(difference_type n)
            {
                current += n;
                return *this;
            }
            vector_iterator_ &operator-=(difference_type n)
            {
                current -= n;
                return *this;
            }
            // offset dereference operator
            reference operator[](difference_type n) const
            {
                return *(current + n);
            }

        private:
            iterator_type current;
    };

    // Non-member functions
    template <class Iterator1, class Iterator2>
    bool operator==(const ft::vector_iterator_<Iterator1> &lhs,
                    const ft::vector_iterator_<Iterator2> &rhs)
    {
        return lhs.base() == rhs.base();
    }
    template <class Iterator1, class Iterator2>
    bool operator!=(const ft::vector_iterator_<Iterator1> &lhs,
                    const ft::vector_iterator_<Iterator2> &rhs)
    {
        return lhs.base() != rhs.base();
    }
    template <class Iterator1, class Iterator2>
    bool operator<(const ft::vector_iterator_<Iterator1> &lhs,
                   const ft::vector_iterator_<Iterator2> &rhs)
    {
        return lhs.base() < rhs.base();
    }
    template <class Iterator1, class Iterator2>
    bool operator<=(const ft::vector_iterator_<Iterator1> &lhs,
                    const ft::vector_iterator_<Iterator2> &rhs)
    {
        return lhs.base() <= rhs.base();
    }
    template <class Iterator1, class Iterator2>
    bool operator>(const ft::vector_iterator_<Iterator1> &lhs,
                   const ft::vector_iterator_<Iterator2> &rhs)
    {
        return lhs.base() > rhs.base();
    }
    template <class Iterator1, class Iterator2>
    bool operator>=(const ft::vector_iterator_<Iterator1> &lhs,
                    const ft::vector_iterator_<Iterator2> &rhs)
    {
        return lhs.base() >= rhs.base();
    }

    template <class Iterator>
    vector_iterator_<Iterator> operator+(
        typename vector_iterator_<Iterator>::difference_type n,
        const vector_iterator_<Iterator> &it)
    {
        return vector_iterator_<Iterator>(it.base() + n);
    }
    template <class Iterator>
    typename vector_iterator_<Iterator>::difference_type
    operator-(const vector_iterator_<Iterator> &lhs,
              const vector_iterator_<Iterator> &rhs)
    {
        return lhs.base() - rhs.base();
    }


    template <class T, class Allocator = std::allocator<T> >
    class vector
    {
        public:
            // Member types
            typedef T                                        value_type;
            typedef Allocator                                allocator_type;
            typedef typename allocator_type::reference       reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::pointer         pointer;
            typedef typename allocator_type::const_pointer   const_pointer;
            typedef vector_iterator_<pointer>                  iterator;
            typedef vector_iterator_<const_pointer>            const_iterator;
            typedef typename allocator_type::size_type       size_type;
            typedef typename allocator_type::difference_type difference_type;
            typedef ft::reverse_iterator<iterator>               reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

            // Member functions
            explicit vector(const allocator_type& alloc = allocator_type()) : alloc_(alloc) {}
            explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : alloc_(alloc)
            {
                allocate(n);
                construct_at_end(n, val);
            }
            template <class InputIterator>
            vector(typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type first,
                   InputIterator last,
                   const allocator_type& alloc = allocator_type()) : alloc_(alloc)
            {
                (void)first;
                (void)last;
            }
            vector(const vector& x)
            {
                (void)x;
            }
            // Member functions: Iterators
            iterator begin()
            {
                return iterator(first_);
            }
            const_iterator begin() const
            {
                return const_iterator(first_);
            }
            iterator end()
            {
                return iterator(last_);
            }
            const_iterator end() const
            {
                return const_iterator(last_);
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
            size_type size() const
            {
                return last_ - first_;
            }
            // Member functions: Capacity
            // Member functions: Element access
            reference operator[] (size_type n)
            {
                return first_[n];
            }
            const_reference operator[] (size_type n) const
            {
                return first_[n];
            }
            // Member functions: Modifiers
            // Member functions: Allocator
            // Non-member functions
        private:
            allocator_type alloc_;
            pointer first_;
            pointer last_;
            pointer capacity_end_;

            void allocate(size_type size)
            {
                first_ = alloc_.allocate(size);
            }

            void construct_at_end(size_type size, const_reference value)
            {
                for (size_type i = 0; i < size; i++)
                {
                    alloc_.construct(first_ + i, value);
                }
                last_ = first_ + size;
                capacity_end_ = last_;
            }
    };

} /* namespace ft */

#endif /* VECTOR_HPP */
