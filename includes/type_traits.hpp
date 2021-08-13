#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft
{
    // iterator_traits
    template <class Iterator>
    struct iterator_traits
    {
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
        typedef typename Iterator::iterator_category iterator_category;
    };

    // enable_if
    template <bool B, class T = void>
    struct enable_if {};

    template <class T>
    struct enable_if<true, T>
    {
        typedef T type;
    };

} /* namespace ft */

#endif /* TYPE_TRAITS_HPP */
