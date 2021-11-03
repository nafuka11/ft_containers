#ifndef ARGPARSER_HPP
#define ARGPARSER_HPP

#include <string>

class ArgParser
{
private:
    static const std::string CONTAINER_NAMES[];
    static void (*const OUTPUT_TEST_FUNCS[])(void);
    static void (*const BENCHMARK_TEST_FUNCS[])(void);
    static const size_t CONTAINER_LEN;

    bool is_benchmark_;

    bool parse_arg(char *arg);
    int parse_flags(int argc, char *argv[]);
    bool parse_flag(char *arg);
    void test_all();
    void test_container(int index);
    void print_help(char *program_name);

public:
    ArgParser();
    ~ArgParser();

    void parse_args(int argc, char *argv[]);
};

#endif /* ARGPARSER_HPP */
