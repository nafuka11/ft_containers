#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

#include <iterator>

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
    template <class T>
    struct iterator_traits<T*>
    {
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef std::random_access_iterator_tag iterator_category;
    };
    template <class T>
    struct iterator_traits<const T*>
    {
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef const T* pointer;
        typedef const T& reference;
        typedef std::random_access_iterator_tag iterator_category;
    };

    // enable_if
    template <bool B, class T = void>
    struct enable_if {};

    template <class T>
    struct enable_if<true, T>
    {
        typedef T type;
    };

    // remove_cv
    template <class T>
    struct remove_cv
    {
        typedef T type;
    };

    template <class T>
    struct remove_cv<const T>
    {
        typedef T type;
    };

    template <class T>
    struct remove_cv<volatile T>
    {
        typedef T type;
    };

    template <class T>
    struct remove_cv<const volatile T>
    {
        typedef T type;
    };

    // integral_constant
    template <class T, T v>
    struct integral_constant
    {
        enum { value = v };
        typedef T value_type;
        typedef integral_constant type;
        operator value_type() const
        {
            return value;
        }
    };
    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;

    // is_integral
    template <class T>
    struct is_integral_helper : public false_type {};
    template <>
    struct is_integral_helper<bool> : public true_type {};
    template <>
    struct is_integral_helper<char> : public true_type {};
    template <>
    struct is_integral_helper<signed char> : public true_type {};
    template <>
    struct is_integral_helper<unsigned char> : public true_type {};
    template <>
    struct is_integral_helper<wchar_t> : public true_type {};
    template <>
    struct is_integral_helper<char16_t> : public true_type {};
    template <>
    struct is_integral_helper<char32_t> : public true_type {};
    template <>
    struct is_integral_helper<short> : public true_type {};
    template <>
    struct is_integral_helper<unsigned short> : public true_type {};
    template <>
    struct is_integral_helper<int> : public true_type {};
    template <>
    struct is_integral_helper<unsigned int> : public true_type {};
    template <>
    struct is_integral_helper<long> : public true_type {};
    template <>
    struct is_integral_helper<unsigned long> : public true_type {};
    template <>
    struct is_integral_helper<long long> : public true_type {};
    template <>
    struct is_integral_helper<unsigned long long> : public true_type {};

    template <class T>
    struct is_integral : public is_integral_helper<typename remove_cv<T>::type> {};

} /* namespace ft */

#endif /* TYPE_TRAITS_HPP */
