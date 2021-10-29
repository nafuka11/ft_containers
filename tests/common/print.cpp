#include <iostream>
#include <string>
#include <iomanip>
#include "common/Timer.hpp"

void print_test_case(const std::string &str)
{
    std::cout << "** " << str << " **" << std::endl;
}

void print_time(const std::string &str, const Timer &timer)
{
    std::cout << std::setw(25) << std::left << str;
    std::cout << timer << std::endl;
}
