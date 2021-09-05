#include "common.hpp"
#include "vector/VectorIteratorTester.hpp"
#include "vector/VectorTester.hpp"

void test_dereference(ft::vector<Foo> &vec_foo)
{
    ft::vector<Foo> vec = vec_foo;
    print_test_case("iter->member");
    {
        for (ft::vector<Foo>::iterator iter = vec.begin(); iter != vec.end(); ++iter)
        {
            std::cout << "(constant:" << iter->getConstant()
                      << ", allocated:" << iter->getAllocated() << ")" << std::endl;
        }
    }
    print_test_case("*iter = Foo(42, 24) -> Foo(-1, 24)");
    {
        ft::vector<Foo>::iterator iter = vec.begin();
        *iter = Foo(42, 24);
        std::cout << "(constant:" << iter->getConstant()
                  << ", allocated:" << iter->getAllocated() << ")" << std::endl;
    }
}

void prepare_vectors(ft::vector<int> &vec_int, ft::vector<Foo> &vec_foo)
{
    for (size_t i = 0; i < vec_int.size(); i++)
    {
        vec_int[i] = i + 1;
    }
    for (size_t i = 0; i < vec_int.size(); i++)
    {
        vec_foo.push_back(Foo(i, i));
    }
}

void test_vector_iterator()
{
    size_t size = 5;
    ft::vector<int> vec_int(size, 42);
    ft::vector<Foo> vec_foo(size);
    prepare_vectors(vec_int, vec_foo);

    VectorIteratorTester<int> tester_int(vec_int);
    VectorIteratorTester<Foo> tester_foo(vec_foo);

    tester_int.test_all();
    tester_foo.test_all();
}

void test_vector()
{
    size_t size = 5;
    ft::vector<int> vec_int(size, 42);
    ft::vector<Foo> vec_foo;
    prepare_vectors(vec_int, vec_foo);

    test_vector_iterator();

    VectorTester<int> tester_int(vec_int);
    VectorTester<Foo> tester_foo(vec_foo);
    tester_int.test_all();
    tester_foo.test_all();
}
