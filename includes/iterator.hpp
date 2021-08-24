#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>
#include "type_traits.hpp"

namespace ft
{
    template <class Iterator>
    class reverse_iterator : public std::iterator<
                                 typename iterator_traits<Iterator>::value_type,
                                 typename iterator_traits<Iterator>::difference_type,
                                 typename iterator_traits<Iterator>::pointer,
                                 typename iterator_traits<Iterator>::reference>
    {
    protected:
        Iterator current;

    public:
        // Member types
        typedef Iterator iterator_type;
        typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
        typedef typename iterator_traits<Iterator>::value_type value_type;
        typedef typename iterator_traits<Iterator>::difference_type difference_type;
        typedef typename iterator_traits<Iterator>::pointer pointer;
        typedef typename iterator_traits<Iterator>::reference reference;

        // Member functions
        // constructor
        reverse_iterator() : current() {}
        explicit reverse_iterator(iterator_type x) : current(x) {}
        // copy constructor
        template <class Iter>
        reverse_iterator(const reverse_iterator<Iter> &other)
        {
            *this = other;
        }
        // destructor
        ~reverse_iterator() {}
        // assignment operator
        template <class Iter>
        reverse_iterator &operator=(const reverse_iterator<Iter> &other)
        {
            if (this != &other)
            {
                current = other.current;
            }
            return *this;
        }

        iterator_type base() const
        {
            return current;
        }

        // dereference operator
        reference operator*() const
        {
            Iterator tmp = current;
            --tmp;
            return *tmp;
        }
        pointer operator->() const
        {
            return &(operator*());
        }
        // offset dereference operator
        reference operator[](difference_type n) const
        {
            return current[-n - 1];
        }
        // prefix/postfix increment
        reverse_iterator &operator++()
        {
            current--;
            return *this;
        }
        reverse_iterator operator++(int)
        {
            reverse_iterator tmp = *this;
            current--;
            return tmp;
        }
        // prefix/postfix decrement
        reverse_iterator &operator--()
        {
            current++;
            return *this;
        }
        reverse_iterator operator--(int)
        {
            reverse_iterator tmp = *this;
            current++;
            return tmp;
        }
        // arithmetic operators
        reverse_iterator operator+(difference_type n) const
        {
            return reverse_iterator(current - n);
        }
        reverse_iterator operator-(difference_type n) const
        {
            return reverse_iterator(current + n);
        }
        // compound assignment operators
        reverse_iterator &operator+=(difference_type n)
        {
            current -= n;
            return *this;
        }
        reverse_iterator &operator-=(difference_type n)
        {
            current += n;
            return *this;
        }
    };

    // Non-member functions
    template <class Iterator1, class Iterator2>
    bool operator==(const ft::reverse_iterator<Iterator1> &lhs,
                    const ft::reverse_iterator<Iterator2> &rhs)
    {
        return lhs.base() == rhs.base();
    }
    template <class Iterator1, class Iterator2>
    bool operator!=(const ft::reverse_iterator<Iterator1> &lhs,
                    const ft::reverse_iterator<Iterator2> &rhs)
    {
        return lhs.base() != rhs.base();
    }
    template <class Iterator1, class Iterator2>
    bool operator<(const ft::reverse_iterator<Iterator1> &lhs,
                   const ft::reverse_iterator<Iterator2> &rhs)
    {
        return lhs.base() > rhs.base();
    }
    template <class Iterator1, class Iterator2>
    bool operator<=(const ft::reverse_iterator<Iterator1> &lhs,
                    const ft::reverse_iterator<Iterator2> &rhs)
    {
        return lhs.base() >= rhs.base();
    }
    template <class Iterator1, class Iterator2>
    bool operator>(const ft::reverse_iterator<Iterator1> &lhs,
                   const ft::reverse_iterator<Iterator2> &rhs)
    {
        return lhs.base() < rhs.base();
    }
    template <class Iterator1, class Iterator2>
    bool operator>=(const ft::reverse_iterator<Iterator1> &lhs,
                    const ft::reverse_iterator<Iterator2> &rhs)
    {
        return lhs.base() <= rhs.base();
    }

    template <class Iterator>
    reverse_iterator<Iterator> operator+(
        typename reverse_iterator<Iterator>::difference_type n,
        const reverse_iterator<Iterator> &it)
    {
        return reverse_iterator<Iterator>(it.base() - n);
    }
    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type
    operator-(const reverse_iterator<Iterator> &lhs,
              const reverse_iterator<Iterator> &rhs)
    {
        return rhs.base() - lhs.base();
    }

} /* namespace ft */

#endif /* ITERATOR_HPP */
