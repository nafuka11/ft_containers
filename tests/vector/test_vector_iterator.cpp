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


void test_vector_iterator()
{
    size_t size = 5;
    ft::vector<int> vec(size, 42);
    for (size_t i = 0; i < size; i++)
    {
        vec[i] = i;
    }

    test_equality_inequality_operator(vec);
}
