#include "common.hpp"

void print_test_case(std::string str)
{
    std::cout << "** " << str << " **" << std::endl;
}

template <class Iter>
void test_equality_inequality_operator(Iter begin, Iter end)
{
    print_test_case("iter == iter");
    {
        std::cout << std::boolalpha << "begin() == begin(): " << (begin == begin) << std::endl;
        std::cout << std::boolalpha << "begin() ==   end(): " << (begin == end) << std::endl;
    }

    print_test_case("iter != iter");
    {
        std::cout << std::boolalpha << "begin() != begin(): " << (begin != begin) << std::endl;
        std::cout << std::boolalpha << "begin() !=   end(): " << (begin != end) << std::endl;
    }
}

void test_dereference(ft::vector<Foo> &vec)
{
    print_test_case("iter->member");
    {
        for (ft::vector<Foo>::iterator iter = vec.begin(); iter != vec.end(); ++iter)
        {
            std::cout << "(constant:" << iter->getConstant() << ", allocated:" << iter->getAllocated() << ")" << std::endl;
        }
    }
    print_test_case("*iter = Foo(42, 24) -> Foo(-1, 24)");
    {
        ft::vector<Foo>::iterator iter = vec.begin();
        *iter = Foo(42, 24);
        std::cout << "(constant:" << iter->getConstant() << ", allocated:" << iter->getAllocated() << ")" << std::endl;
    }
}

template <class Iter>
void test_increment_decrement(Iter begin, Iter end)
{
    print_test_case("++iter");
    {
        for (Iter iter = begin; iter != end; ++iter)
        {
            std::cout << " " << *iter;
        }
        std::cout << std::endl;
    }
    print_test_case("iter++");
    {
        for (Iter iter = begin; iter != end; iter++)
        {
            std::cout << " " << *iter;
        }
        std::cout << std::endl;
    }
    print_test_case("--iter");
    {
        for (Iter iter = end - 1; iter != begin; --iter)
        {
            std::cout << " " << *iter;
        }
        std::cout << std::endl;
    }
    print_test_case("iter--");
    {
        for (Iter iter = end - 1; iter != begin; iter--)
        {
            std::cout << " " << *iter;
        }
        std::cout << std::endl;
    }
}

template <class Iter>
void test_arithmetic_operator(Iter begin, Iter end)
{
    print_test_case("iter + ptrdiff_t(2)");
    std::cout << *(begin + 2) << std::endl;

    print_test_case("ptrdiff_t(2) + iter");
    std::cout << *(2 + begin) << std::endl;

    print_test_case("iter - ptrdiff_t(2)");
    std::cout << *(end - 2) << std::endl;

    print_test_case("iter - iter");
    std::cout << end - begin << std::endl;
}

template <class Iter>
void test_inequality_relational_operator(Iter begin)
{
    print_test_case("<, >, <=, >=");
    {
        Iter first = begin;
        Iter second = first + 1;
        std::cout << std::boolalpha
                  << "first  < first  = " << (first < first) << std::endl
                  << "first  < second = " << (first < second) << std::endl
                  << "first  > first  = " << (first > first) << std::endl
                  << "second > first  = " << (second > first) << std::endl
                  << "first <= first  = " << (first <= first) << std::endl
                  << "first <= second = " << (first <= second) << std::endl
                  << "second<= first  = " << (second <= first) << std::endl
                  << "first >= first  = " << (first >= first) << std::endl
                  << "first >= second = " << (first >= second) << std::endl
                  << "second>= first  = " << (second >= first) << std::endl;
    }
}

template <class Iter>
void test_compound_assignment_operation(Iter begin, Iter end)
{
    print_test_case("iter += ptrdiff_t(3)");
    {
        Iter iter = begin;
        iter += 3;
        std::cout << *iter << std::endl;
    }

    print_test_case("iter -= ptrdiff_t(3)");
    {
        Iter iter = end;
        iter -= 3;
        std::cout << *iter << std::endl;
    }
}

template <class Iter>
void test_offset_difference_operator(Iter begin)
{
    print_test_case("iter[2]");
    {
        std::cout << begin[2] << std::endl;
    }
}

template <class Iter>
void test_iterator_functions(Iter begin, Iter end)
{
    test_equality_inequality_operator(begin, end);
    test_increment_decrement(begin, end);
    test_arithmetic_operator(begin, end);
    test_inequality_relational_operator(begin);
    test_compound_assignment_operation(begin, end);
    test_offset_difference_operator(begin);
}

void prepare_vectors(ft::vector<int> &vecInt, ft::vector<Foo> &vecFoo)
{
    for (size_t i = 0; i < vecInt.size(); i++)
    {
        vecInt[i] = i;
    }
    for (size_t i = 0; i < vecFoo.size(); i++)
    {
        vecFoo[i].setAllocated(i);
    }
}

void test_vector_iterator()
{
    size_t size = 5;
    ft::vector<int> vecInt(size, 42);
    ft::vector<Foo> vecFoo(size);
    prepare_vectors(vecInt, vecFoo);

    ft::vector<int>::iterator begin = vecInt.begin();
    ft::vector<int>::iterator end = vecInt.end();
    ft::vector<int>::const_iterator cbegin = vecInt.begin();
    ft::vector<int>::const_iterator cend = vecInt.end();
    ft::vector<int>::reverse_iterator rbegin = vecInt.rbegin();
    ft::vector<int>::reverse_iterator rend = vecInt.rend();
    ft::vector<int>::const_reverse_iterator crbegin = vecInt.rbegin();
    ft::vector<int>::const_reverse_iterator crend = vecInt.rend();

    test_iterator_functions(begin, end);
    test_iterator_functions(rbegin, rend);
    test_iterator_functions(cbegin, cend);
    test_iterator_functions(crbegin, crend);
    test_iterator_functions(vecFoo.begin(), vecFoo.end());
    test_iterator_functions(vecFoo.rbegin(), vecFoo.rend());
    test_dereference(vecFoo);
}
