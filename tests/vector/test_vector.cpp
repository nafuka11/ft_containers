#include "common.hpp"
#include "vector/VectorIteratorTester.hpp"

void test_dereference(ft::vector<Foo> &vecFoo)
{
    ft::vector<Foo> vec = vecFoo;
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

    VectorIteratorTester<int> testerInt(vecInt);
    VectorIteratorTester<Foo> testerFoo(vecFoo);

    testerInt.test_all();
    testerFoo.test_all();
}
