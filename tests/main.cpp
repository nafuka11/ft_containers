#include <cstdlib>
#include "common/ArgParser.hpp"
#include "test.hpp"

#if IS_FT
#define EXE_NAME "tester_ft"
#else
#define EXE_NAME "tester_stl"
#endif

int main(int argc, char *argv[])
{
    ArgParser parser;
    parser.parse_args(argc, argv);
    system("leaks " EXE_NAME "| grep bytes | sed 's/^Process [0-9]*: //'");
}
