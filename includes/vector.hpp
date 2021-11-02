#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <algorithm>
#include <exception>
#include <limits>
#include <memory>
#include "algorithm.hpp"
#include "iterator.hpp"

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
        typedef T value_type;
        typedef Allocator allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef vector_iterator_<pointer> iterator;
        typedef vector_iterator_<const_pointer> const_iterator;
        typedef typename allocator_type::size_type size_type;
        typedef typename allocator_type::difference_type difference_type;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

        // Member functions
        explicit vector(const allocator_type &alloc = allocator_type())
            : alloc_(alloc), first_(NULL), last_(NULL), capacity_last_(NULL) {}
        explicit vector(size_type count, const value_type &value = value_type(),
                        const allocator_type &alloc = allocator_type())
            : alloc_(alloc), first_(NULL), last_(NULL), capacity_last_(NULL)
        {
            if (count > 0)
            {
                allocate(count);
                std::uninitialized_fill_n(first_, count, value);
            }
        }
        template <class InputIterator>
        vector(InputIterator first,
               typename ft::enable_if<
                   !ft::is_integral<InputIterator>::value, InputIterator>::type last,
               const allocator_type &alloc = allocator_type()) : alloc_(alloc)
        {
            allocate(std::distance(first, last));
            std::uninitialized_copy(first, last, first_);
        }
        vector(const vector &other)
            : alloc_(other.alloc_), first_(NULL), last_(NULL), capacity_last_(NULL)
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
        vector &operator=(const vector &other)
        {
            assign(other.first_, other.last_);
            return *this;
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
            return std::min(
                static_cast<size_type>(std::numeric_limits<difference_type>::max()),
                alloc_.max_size());
        }
        void resize(size_type count, value_type value = value_type())
        {
            if (count < size())
            {
                erase(begin() + count, end());
            }
            else if (count > size())
            {
                insert(end(), count - size(), value);
            }
        }
        size_type capacity() const
        {
            return capacity_last_ - first_;
        }
        bool empty() const
        {
            return first_ == last_;
        }
        void reserve(size_type new_cap)
        {
            if (new_cap > max_size())
                throw std::length_error(
                    "allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
            if (new_cap > capacity())
            {
                size_type old_capacity = capacity();
                size_type old_size = size();
                pointer new_first = alloc_.allocate(new_cap);

                std::uninitialized_copy(first_, last_, new_first);
                clear();
                alloc_.deallocate(first_, old_capacity);
                first_ = new_first;
                last_ = first_ + old_size;
                capacity_last_ = first_ + new_cap;
            }
        }

        // Member functions: Element access
        reference operator[](size_type pos)
        {
            return first_[pos];
        }
        const_reference operator[](size_type pos) const
        {
            return first_[pos];
        }
        reference at(size_type pos)
        {
            if (pos >= size())
                throw std::out_of_range("vector");
            return first_[pos];
        }
        const_reference at(size_type pos) const
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
        template <class InputIterator>
        void assign(InputIterator first,
                    typename ft::enable_if<
                        !ft::is_integral<InputIterator>::value, InputIterator>::type last)
        {
            size_type new_size = std::distance(first, last);
            if (new_size > capacity())
            {
                clear();
                reserve(new_size);
                std::uninitialized_copy(first, last, first_);
            }
            else
            {
                destruct_at_end(first_ + new_size);
                std::copy(first, last, first_);
            }
            last_ = first_ + new_size;
        }
        void assign(size_type count, const T &value)
        {
            if (count > capacity())
            {
                clear();
                reserve(count);
                std::uninitialized_fill_n(first_, count, value);
            }
            else
            {
                destruct_at_end(first_ + count);
                std::fill_n(first_, count, value);
            }
            last_ = first_ + count;
        }

        // Member functions: Modifiers
        void push_back(const value_type &value)
        {
            size_type new_size = size() + 1;
            if (new_size > capacity())
            {
                reserve(calc_new_capacity(new_size));
            }
            alloc_.construct(last_, value);
            last_++;
        }
        void pop_back()
        {
            destruct_at_end(last_ - 1);
        }
        iterator insert(iterator pos, const value_type &value)
        {
            size_type offset = pos - begin();
            insert(pos, 1, value);
            return begin() + offset;
        }
        void insert(iterator pos, size_type count, const value_type &value)
        {
            size_type new_size = size() + count;
            size_type offset = pos - begin();

            if (new_size > capacity())
            {
                new_size = calc_new_capacity(new_size);
                size_type old_capacity = capacity();
                size_type old_size = size();
                pointer new_first = alloc_.allocate(new_size);

                std::uninitialized_copy(begin(), pos, new_first);
                std::uninitialized_fill_n(new_first + offset, count, value);
                std::uninitialized_copy(pos, end(), new_first + offset + count);

                clear();
                alloc_.deallocate(first_, old_capacity);
                first_ = new_first;
                last_ = first_ + old_size + count;
                capacity_last_ = first_ + new_size;
            }
            else
            {
                move_range(offset, count);
                for (size_type i = 0; i < count; i++)
                {
                    if (offset + i >= size())
                    {
                        alloc_.construct(&first_[offset + i], value);
                    }
                    else
                    {
                        first_[offset + i] = value;
                    }
                }
                last_ += count;
            }
        }
        template <class InputIterator>
        void insert(iterator pos, InputIterator first,
                    typename ft::enable_if<
                        !ft::is_integral<InputIterator>::value, InputIterator>::type last)
        {
            size_type count = std::distance(first, last);
            size_type new_size = size() + count;
            size_type offset = pos - begin();

            if (new_size > capacity())
            {
                new_size = calc_new_capacity(new_size);
                size_type old_capacity = capacity();
                size_type old_size = size();
                pointer new_first = alloc_.allocate(new_size);

                std::uninitialized_copy(begin(), pos, new_first);
                std::uninitialized_copy(first, last, new_first + offset);
                std::uninitialized_copy(pos, end(), new_first + offset + count);

                clear();
                alloc_.deallocate(first_, old_capacity);
                first_ = new_first;
                last_ = first_ + old_size + count;
                capacity_last_ = first_ + new_size;
            }
            else
            {
                move_range(offset, count);
                for (size_type i = 0; i < count; i++)
                {
                    if (offset + i >= size())
                    {
                        alloc_.construct(&first_[offset + i], *first);
                    }
                    else
                    {
                        first_[offset + i] = *first;
                    }
                    ++first;
                }
                last_ += count;
            }
        }
        iterator erase(iterator pos)
        {
            return erase(pos, pos + 1);
        }
        iterator erase(iterator first, iterator last)
        {
            difference_type offset = std::distance(first, last);
            for (iterator iter = first; iter + offset != end(); ++iter)
            {
                *iter = *(iter + offset);
            }
            destruct_at_end(last_ - offset);
            return first;
        }
        void swap(vector &other)
        {
            pointer tmp_first = other.first_;
            pointer tmp_last = other.last_;
            pointer tmp_capacity_last = other.capacity_last_;

            other.first_ = first_;
            other.last_ = last_;
            other.capacity_last_ = capacity_last_;
            first_ = tmp_first;
            last_ = tmp_last;
            capacity_last_ = tmp_capacity_last;
        }
        void clear()
        {
            destruct_at_end(first_);
        }

        // Member functions: Allocator
        allocator_type get_allocator() const
        {
            return alloc_;
        }

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
        size_type calc_new_capacity(size_type new_cap)
        {
            size_type max_cap = max_size();
            if (new_cap > max_cap)
                throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
            size_type cap = capacity();
            if (cap >= max_cap / 2)
                return max_cap;
            return std::max(cap * 2, new_cap);
        }
        void move_range(size_type offset, size_type count)
        {
            size_type now_size = size();
            size_type new_size = now_size + count;

            for (size_t i = 0; i < now_size - offset; i++)
            {
                if (new_size - i > now_size)
                {
                    alloc_.construct(&first_[new_size - i - 1], first_[now_size - i - 1]);
                }
                else
                {
                    first_[new_size - i - 1] = first_[now_size - i - 1];
                }
            }
        }
    };

    // vector: Non-member functions
    template <class T, class Alloc>
    bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }
    template <class T, class Alloc>
    bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return !(lhs == rhs);
    }
    template <class T, class Alloc>
    bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
    template <class T, class Alloc>
    bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return !(rhs < lhs);
    }
    template <class T, class Alloc>
    bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return rhs < lhs;
    }
    template <class T, class Alloc>
    bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return !(lhs < rhs);
    }
    template <class T, class Alloc>
    void swap(ft::vector<T, Alloc> &lhs, ft::vector<T, Alloc> &rhs)
    {
        lhs.swap(rhs);
    }

} /* namespace ft */

#endif /* VECTOR_HPP */
