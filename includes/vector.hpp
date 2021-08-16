#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "type_traits.hpp"

namespace ft
{
    template <class T>
    class vector_iterator_ : public std::iterator<std::random_access_iterator_tag, T>
    {
        public:
            typedef typename std::iterator<std::random_access_iterator_tag, T>::value_type          value_type;
            typedef typename std::iterator<std::random_access_iterator_tag, T>::difference_type     difference_type;
            typedef typename std::iterator<std::random_access_iterator_tag, T>::pointer             pointer;
            typedef typename std::iterator<std::random_access_iterator_tag, T>::reference           reference;
            typedef typename std::iterator<std::random_access_iterator_tag, T>::iterator_category   iterator_category;

            // constructor
            vector_iterator_() : ptr_(NULL) {}
            vector_iterator_(pointer ptr) : ptr_(ptr) {}
            // copy constructor
            vector_iterator_(const vector_iterator_ &iter)
            {
                *this = iter;
            }
            // assignment operator
            vector_iterator_ &operator=(const vector_iterator_ &iter)
            {
                if (this != &iter)
                {
                    ptr_ = iter.ptr_;
                }
                return *this;
            }
            // destructor
            ~vector_iterator_() {}

        private:
            pointer ptr_;
    };


} /* namespace ft */

#endif /* VECTOR_HPP */
