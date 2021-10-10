#include "ArgParser.hpp"
#include "test.hpp"

const std::string ArgParser::container_names[] = {
    "vector",
    "map"
};

void (*const ArgParser::container_funcs[])(void) = {
    test_vector,
    test_map
};

const size_t ArgParser::container_len =
    sizeof(container_names) / sizeof(container_names[0]);

ArgParser::ArgParser()
{
}

ArgParser::~ArgParser()
{
}

void ArgParser::parse_args(int argc, char *argv[])
{
    if (argc == 1)
    {
        test_all();
        return;
    }
    for (int i = 1; i < argc; i++)
    {
        if (!parse_arg(argv[i]))
        {
            print_help(argv[0]);
            return;
        }
    }
}

bool ArgParser::parse_arg(char *arg)
{
    std::string arg_str = arg;
    for (size_t i = 0; i < container_len; i++)
    {
        if (arg_str == container_names[i])
        {
            container_funcs[i]();
            return true;
        }
    }
    return false;
}

void ArgParser::test_all()
{
    for (size_t i = 0; i < container_len; i++)
    {
        container_funcs[i]();
    }
}

void ArgParser::print_help(char *program_name)
{
    std::cout << program_name << " [";
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
