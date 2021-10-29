#include <iostream>
#include "ArgParser.hpp"
#include "test.hpp"

const std::string ArgParser::container_names[] = {
    "vector",
    "map",
    "stack"
};

void (*const ArgParser::output_test_funcs[])(void) = {
    test_vector_output,
    test_map_output,
    test_stack_output
};

void (*const ArgParser::benchmark_test_funcs[])(void) = {
    test_vector_benchmark,
    test_map_output,
    test_stack_output
};

const size_t ArgParser::container_len =
    sizeof(container_names) / sizeof(container_names[0]);

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
    for (size_t i = 0; i < container_len; i++)
    {
        if (arg_str == container_names[i])
        {
            test_container(i);
            return true;
        }
    }
    return false;
}

void ArgParser::test_all()
{
    for (size_t i = 0; i < container_len; i++)
    {
        test_container(i);
    }
}

void ArgParser::test_container(int index)
{
    if (is_benchmark_)
    {
        benchmark_test_funcs[index]();
    }
    else
    {
        output_test_funcs[index]();
    }
}

void ArgParser::print_help(char *program_name)
{
    std::cout << "Usage: " << program_name << " [-b] [";
    for (size_t i = 0; i < container_len; i++)
    {
        std::cout << container_names[i];
        if (i != container_len - 1)
        {
            std::cout << " ";
        }
    }
    std::cout << "]" << std::endl;
}
