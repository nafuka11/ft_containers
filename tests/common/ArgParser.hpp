#ifndef ARGPARSER_HPP
#define ARGPARSER_HPP

#include <string>

class ArgParser
{
private:
    static const std::string container_names[];
    static void (*const container_funcs[])(void);
    static const size_t container_len;

    bool parse_arg(char *arg);
    void test_all();
    void print_help(char *program_name);

public:
    ArgParser();
    ~ArgParser();

    void parse_args(int argc, char *argv[]);
};

#endif /* ARGPARSER_HPP */
