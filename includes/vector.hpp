#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <limits>
#include <exception>
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
            explicit vector(const allocator_type& alloc = allocator_type()) : alloc_(alloc), first_(NULL), last_(NULL), capacity_last_(NULL) {}
            explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : alloc_(alloc)
            {
                allocate(n);
                construct_at_end(n, val);
            }
            // TODO: push_backを実装する
            // template <class InputIterator>
            // vector(typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type first,
            //        InputIterator last,
            //        const allocator_type& alloc = allocator_type()) : alloc_(alloc)
            // {
            //     (void) first;
            //     (void) last;
            // }
            vector(const vector& other) : first_(NULL), last_(NULL), capacity_last_(NULL)
            {
                size_type size = other.size();
                if (size > 0)
                {
                    allocate(size);
                    std::uninitialized_copy(other.first_, other.last_, first_);
                }
            }
            ~vector()
            {
                clear();
                deallocate();
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
            // Member functions: Capacity
            size_type size() const
            {
                return last_ - first_;
            }
            size_type max_size() const
            {
                return std::min(static_cast<size_type>(std::numeric_limits<difference_type>::max()),
                                std::numeric_limits<size_type>::max() /sizeof(value_type));
            }
            // void resize (size_type count, value_type value = value_type());
            size_type capacity() const
            {
                return capacity_last_ - first_;
            }
            bool empty() const
            {
                return first_ == last_;
            }
            // void reserve( size_type new_cap );

            // Member functions: Element access
            reference operator[] (size_type pos)
            {
                return first_[pos];
            }
            const_reference operator[] (size_type pos) const
            {
                return first_[pos];
            }
            reference at(size_type pos)
            {
                if (pos >= size())
                    throw std::out_of_range("vector");
                return first_[pos];
            }
            const_reference at( size_type pos ) const
            {
                if (pos >= size())
                    throw std::out_of_range("vector");
                return first_[pos];
            }
            reference front()
            {
                return *begin();
            }
            const_reference front() const
            {
                return *begin();
            }
            reference back()
            {
                return *(end() - 1);
            }
            const_reference back() const
            {
                return *(end() - 1);
            }
            // Member functions: Modifiers
            void pop_back()
            {
                destruct_at_end(last_ - 1);
            }
            void clear()
            {
                destruct_at_end(first_);
            }

            // Member functions: Allocator
            // Non-member functions

        private:
            allocator_type alloc_;
            pointer first_;
            pointer last_;
            pointer capacity_last_;

            void allocate(size_type size)
            {
                first_ = alloc_.allocate(size);
                last_ = first_ + size;
                capacity_last_ = last_;
            }
            void deallocate()
            {
                alloc_.deallocate(first_, capacity());
            }
            void destruct_at_end(pointer new_last)
            {
                pointer now = last_;
                while (now != new_last)
                {
                    alloc_.destroy(--now);
                }
                last_ = new_last;
            }
    };

} /* namespace ft */

#endif /* VECTOR_HPP */
