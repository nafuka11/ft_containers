#include "common.hpp"

void print_test_case(std::string str)
{
    std::cout << "** " << str << " **" << std::endl;
}

void test_equality_inequality_operator(ft::vector<int> &vec)
{
    print_test_case("iter == iter");
    {
        std::cout << std::boolalpha << "begin() == begin(): " << (vec.begin() == vec.begin()) << std::endl;
        std::cout << std::boolalpha << "begin() ==   end(): " << (vec.begin() == vec.end()) << std::endl;
    }

    print_test_case("iter != iter");
    {
        std::cout << std::boolalpha << "begin() != begin(): " << (vec.begin() != vec.begin()) << std::endl;
        std::cout << std::boolalpha << "begin() !=   end(): " << (vec.begin() != vec.end()) << std::endl;
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

void test_increment_decrement(ft::vector<int> &vec)
{
    print_test_case("++iter");
    {
        for (ft::vector<int>::iterator iter = vec.begin(); iter != vec.end(); ++iter)
        {
            std::cout << " " << *iter;
        }
        std::cout << std::endl;
    }
    print_test_case("iter++");
    {
        for (ft::vector<int>::iterator iter = vec.begin(); iter != vec.end(); iter++)
        {
            std::cout << " " << *iter;
        }
        std::cout << std::endl;
    }
    // TODO: reverse iteratorを実装したらコメントアウト解除
    // print_test_case("--iter");
    // {
    //     for (ft::vector<int>::iterator iter = vec.end(); iter != vec.begin(); --iter)
    //     {
    //         std::cout << " " << *iter;
    //     }
    //     std::cout << std::endl;
    // }
    // print_test_case("iter--");
    // {
    //     for (ft::vector<int>::iterator iter = vec.end(); iter != vec.begin(); iter--)
    //     {
    //         std::cout << " " << *iter;
    //     }
    //     std::cout << std::endl;
    // }
}

void test_arithmetic_operator(ft::vector<int> &vec)
{
    print_test_case("iter + ptrdiff_t(2)");
    std::cout << *(vec.begin() + 2) << std::endl;

    print_test_case("ptrdiff_t(2) + iter");
    std::cout << *(2 + vec.begin()) << std::endl;

    print_test_case("iter - ptrdiff_t(2)");
    std::cout << *(vec.end() - 2) << std::endl;

    print_test_case("iter - iter");
    std::cout << vec.end() - vec.begin() << std::endl;
}

void test_inequality_relational_operator(ft::vector<int> &vec)
{
    print_test_case("<, >, <=, >=");
    {
        ft::vector<int>::iterator first = vec.begin();
        ft::vector<int>::iterator second = first + 1;
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

void test_compound_assignment_operation(ft::vector<int> &vec)
{
    print_test_case("iter += ptrdiff_t(3)");
    {
        ft::vector<int>::iterator iter = vec.begin();
        iter += 3;
        std::cout << *iter << std::endl;
    }

    print_test_case("iter -= ptrdiff_t(3)");
    {
        ft::vector<int>::iterator iter = vec.end();
        iter -= 3;
        std::cout << *iter << std::endl;
    }
}

void test_offset_difference_operator(ft::vector<int> &vec)
{
    print_test_case("iter[2]");
    {
        ft::vector<int>::iterator iter = vec.begin();
        std::cout << iter[2] << std::endl;
    }
}

void test_vector_iterator()
{
    size_t size = 5;
    ft::vector<int> vecInt(size, 42);
    for (size_t i = 0; i < size; i++)
    {
        vecInt[i] = i;
    }

    ft::vector<Foo> vecFoo(size);
    for (size_t i = 0; i < size; i++)
    {
        vecFoo[i].setAllocated(i);
    }

    test_equality_inequality_operator(vecInt);
    test_dereference(vecFoo);
    test_increment_decrement(vecInt);
    test_arithmetic_operator(vecInt);
    test_inequality_relational_operator(vecInt);
    test_compound_assignment_operation(vecInt);
    test_offset_difference_operator(vecInt);
}
