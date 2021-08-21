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


void test_vector_iterator()
{
    size_t size = 5;
    ft::vector<int> vec(size, 42);
    for (size_t i = 0; i < size; i++)
    {
        vec[i] = i;
    }

    test_equality_inequality_operator(vec);
    test_increment_decrement(vec);
    test_arithmetic_operator(vec);
}
