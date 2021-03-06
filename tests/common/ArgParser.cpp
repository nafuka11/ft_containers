#include <iostream>
#include "ArgParser.hpp"
#include "test.hpp"

const std::string ArgParser::CONTAINER_NAMES[] = {
    "vector",
    "map",
    "stack",
    "set"
};

void (*const ArgParser::OUTPUT_TEST_FUNCS[])(void) = {
    test_vector_output,
    test_map_output,
    test_stack_output,
    test_set_output
};

void (*const ArgParser::BENCHMARK_TEST_FUNCS[])(void) = {
    test_vector_benchmark,
    test_map_benchmark,
    test_stack_benchmark,
    test_set_benchmark
};

const size_t ArgParser::CONTAINER_LEN =
    sizeof(CONTAINER_NAMES) / sizeof(CONTAINER_NAMES[0]);

ArgParser::ArgParser() : is_benchmark_(false)
{
}

ArgParser::~ArgParser()
{
}

void ArgParser::parse_args(int argc, char *argv[])
{
    int index = parse_flags(argc, argv);
    if (index == argc)
    {
        test_all();
        return;
    }
    for (int i = index; i < argc; i++)
    {
        if (!parse_arg(argv[i]))
        {
            print_help(argv[0]);
            return;
        }
    }
}

int ArgParser::parse_flags(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        if (!parse_flag(argv[i]))
        {
            return i;
        }
    }
    return argc;
}

bool ArgParser::parse_flag(char *arg)
{
    std::string arg_str = arg;
    if (arg_str == "-b")
    {
        is_benchmark_ = true;
        return true;
    }
    return false;
}

bool ArgParser::parse_arg(char *arg)
{
    std::string arg_str = arg;
    for (size_t i = 0; i < CONTAINER_LEN; i++)
    {
        if (arg_str == CONTAINER_NAMES[i])
        {
            test_container(i);
            return true;
        }
    }
    return false;
}

void ArgParser::test_all()
{
    for (size_t i = 0; i < CONTAINER_LEN; i++)
    {
        test_container(i);
    }
}

void ArgParser::test_container(int index)
{
    if (is_benchmark_)
    {
        BENCHMARK_TEST_FUNCS[index]();
    }
    else
    {
        OUTPUT_TEST_FUNCS[index]();
    }
}

void ArgParser::print_help(char *program_name)
{
    std::cout << "Usage: " << program_name << " [-b] [";
    for (size_t i = 0; i < CONTAINER_LEN; i++)
    {
        std::cout << CONTAINER_NAMES[i];
        if (i != CONTAINER_LEN - 1)
        {
            std::cout << " ";
        }
    }
    std::cout << "]" << std::endl;
}
