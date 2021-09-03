#ifndef PAIRTESTER_HPP
#define PAIRTESTER_HPP

#include "common.hpp"

class PairTester
{
public:
    PairTester();
    ~PairTester();
    void test_all();

private:
    void test_constructor();
    void test_assignment_operator();
    void test_relational_operator();
};

std::ostream &operator<<(std::ostream &os, ft::pair<int, int> const &pair);

#endif /* PAIRTESTER_HPP */
