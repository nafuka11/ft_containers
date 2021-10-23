#ifndef STACKTESTER_HPP
#define STACKTESTER_HPP

#include <typeinfo>
#include "test.hpp"

template <class T, class Container>
class StackTester
{
public:
    StackTester(const Container &cont, const T &elem)
        : cont_(cont), elem_(elem) {}

    void test_all()
    {
        test_constructor();
        test_push();
        test_pop();
        test_relational_operators();
    }

private:
    Container cont_;
    T elem_;

    void test_constructor()
    {
        print_test_case("stack() : constructor");
        ft::stack<T, Container> stk(cont_);
        print_stack(stk);
    }

    void test_push()
    {
        print_test_case("stack::push()");
        ft::stack<T, Container> stk(cont_);
        stk.push(elem_);
        print_stack(stk);
    }

    void test_pop()
    {
        print_test_case("stack::pop()");
        ft::stack<T, Container> stk(cont_);
        while (stk.size() != 0)
        {
            stk.pop();
            print_stack(stk);
        }
    }

    void test_relational_operators()
    {
        ft::stack<T, Container> stk_org(cont_);
        ft::stack<T, Container> stk_less(cont_);
        stk_less.pop();
        ft::stack<T, Container> stk_more(cont_);
        stk_more.push(elem_);

        std::cout << std::boolalpha
                  << "org == org  : " << (stk_org == stk_org) << std::endl
                  << "org == less : " << (stk_org == stk_less) << std::endl
                  << "org == more : " << (stk_org == stk_more) << std::endl;
        std::cout << std::boolalpha
                  << "org != org  : " << (stk_org != stk_org) << std::endl
                  << "org != less : " << (stk_org != stk_less) << std::endl
                  << "org != more : " << (stk_org != stk_more) << std::endl;
        std::cout << std::boolalpha
                  << "org <  org  : " << (stk_org < stk_org) << std::endl
                  << "org <  less : " << (stk_org < stk_less) << std::endl
                  << "org <  more : " << (stk_org < stk_more) << std::endl;
        std::cout << std::boolalpha
                  << "org <= org  : " << (stk_org <= stk_org) << std::endl
                  << "org <= less : " << (stk_org <= stk_less) << std::endl
                  << "org <= more : " << (stk_org <= stk_more) << std::endl;
        std::cout << std::boolalpha
                  << "org >  org  : " << (stk_org > stk_org) << std::endl
                  << "org >  less : " << (stk_org > stk_less) << std::endl
                  << "org >  more : " << (stk_org > stk_more) << std::endl;
        std::cout << std::boolalpha
                  << "org >= org  : " << (stk_org >= stk_org) << std::endl
                  << "org >= less : " << (stk_org >= stk_less) << std::endl
                  << "org >= more : " << (stk_org >= stk_more) << std::endl;
    }

    void print_stack(const ft::stack<T, Container> &stk)
    {
        std::cout << "size()=" << stk.size()
                  << ", empty()=" << stk.empty();
        if (stk.size())
        {
            std::cout << ", top()=" << stk.top();
        }
        std::cout << std::endl;
    }
};

#endif /* STACKTESTER_HPP */
