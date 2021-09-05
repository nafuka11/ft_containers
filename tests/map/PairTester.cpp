#include <iostream>
#include "map/PairTester.hpp"

PairTester::PairTester() {}

PairTester::~PairTester() {}

void PairTester::test_all()
{
    print_test_case("pair");

    test_constructor();
    test_assignment_operator();
    test_relational_operator();
    test_make_pair();
}

void PairTester::test_constructor()
{
    ft::pair<int, int> p1;
    std::cout << "pair<int, int>(): " << p1 << std::endl;

    ft::pair<int, int> p2(1, 2);
    std::cout << "pair<int, int>(1, 2): " << p2 << std::endl;

    ft::pair<int, int> p3(1, 2);
    std::cout << "pair<int, int>(pair(1, 2)): " << p3 << std::endl;
}

void PairTester::test_assignment_operator()
{
    ft::pair<int, int> p1(12, 34);
    ft::pair<int, int> p2(56, 78);
    p2 = p1;
    std::cout << "pair<int, int> p = " << p1 << ": " << p2 << std::endl;
}

std::ostream &operator<<(std::ostream &os, ft::pair<int, int> const &pair)
{
    os << "pair(" << pair.first << ", " << pair.second << ")";
    return os;
}

void PairTester::test_relational_operator()
{
    ft::pair<int, int> p1(1, 1);
    ft::pair<int, int> p2(2, 1);
    ft::pair<int, int> p3(1, 2);

    std::cout << std::boolalpha
              << p1 << " == " << p1 << ": " << (p1 == p1) << std::endl
              << p1 << " == " << p2 << ": " << (p1 == p2) << std::endl
              << p1 << " == " << p3 << ": " << (p1 == p3) << std::endl
              << p1 << " != " << p1 << ": " << (p1 != p1) << std::endl
              << p1 << " != " << p2 << ": " << (p1 != p2) << std::endl
              << p1 << " != " << p3 << ": " << (p1 != p3) << std::endl
              << p1 << " <  " << p1 << ": " << (p1 < p1) << std::endl
              << p1 << " <  " << p2 << ": " << (p1 < p2) << std::endl
              << p1 << " <  " << p3 << ": " << (p1 < p3) << std::endl
              << p2 << " <  " << p1 << ": " << (p2 < p1) << std::endl
              << p3 << " <  " << p1 << ": " << (p3 < p1) << std::endl
              << p1 << " <= " << p1 << ": " << (p1 <= p1) << std::endl
              << p1 << " <= " << p2 << ": " << (p1 <= p2) << std::endl
              << p1 << " <= " << p3 << ": " << (p1 <= p3) << std::endl
              << p2 << " <= " << p1 << ": " << (p2 <= p1) << std::endl
              << p3 << " <= " << p1 << ": " << (p3 <= p1) << std::endl
              << p1 << " >  " << p1 << ": " << (p1 > p1) << std::endl
              << p1 << " >  " << p2 << ": " << (p1 > p2) << std::endl
              << p1 << " >  " << p3 << ": " << (p1 > p3) << std::endl
              << p2 << " >  " << p1 << ": " << (p2 > p1) << std::endl
              << p3 << " >  " << p1 << ": " << (p3 > p1) << std::endl
              << p1 << " >= " << p1 << ": " << (p1 >= p1) << std::endl
              << p1 << " >= " << p2 << ": " << (p1 >= p2) << std::endl
              << p1 << " >= " << p3 << ": " << (p1 >= p3) << std::endl
              << p2 << " >= " << p1 << ": " << (p2 >= p1) << std::endl
              << p3 << " >= " << p1 << ": " << (p3 >= p1) << std::endl;
}

void PairTester::test_make_pair()
{
    std::cout << ft::make_pair<int, int>(1, 2) << std::endl;
}
