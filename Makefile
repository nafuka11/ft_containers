NAME_STL	:= tester_stl
NAME_FT		:= tester_ft

TEST_SCRIPT	:= ./grademe.sh

SRCS		:= tests/main.cpp \
			   tests/common/print.cpp tests/common/ArgParser.cpp tests/common/Foo.cpp tests/common/Timer.cpp \
			   tests/vector/test_vector.cpp tests/vector/VectorBenchmark.cpp \
			   tests/map/test_map.cpp tests/map/PairTester.cpp tests/map/MapBenchmark.cpp \
			   tests/stack/test_stack.cpp

OBJDIR_FT	:= ./objs_ft
OBJDIR_STL	:= ./objs_stl
OBJS_FT		:= $(addprefix $(OBJDIR_FT)/, $(SRCS:.cpp=.o))
OBJS_STL	:= $(addprefix $(OBJDIR_STL)/, $(SRCS:.cpp=.o))

INC			:= -I./includes -I./tests

CXX			:= clang++
CXXFLAGS	:= -Wall -Wextra -Werror -std=c++98 $(INC)

.PHONY	: all
all		: $(NAME_STL) $(NAME_FT) ## Build executables

$(NAME_STL)	: $(OBJS_STL)
	$(CXX) $(CXXFLAGS) -o $(NAME_STL) $(OBJS_STL)

$(NAME_FT)	: $(OBJS_FT)
	$(CXX) $(CXXFLAGS) -o $(NAME_FT) -D IS_FT=1 $(OBJS_FT)

$(OBJDIR_STL)/%.o: %.cpp
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(OBJDIR_FT)/%.o: %.cpp
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CXX) $(CXXFLAGS) -o $@ -D IS_FT=1 -c $<

.PHONY		: clean
clean		: clean ## Delete object files
	$(RM) $(OBJS_STL) $(OBJS_FT)

.PHONY		: fclean
fclean		: clean ## Delete executables
	$(RM) $(NAME_STL) $(NAME_FT)

.PHONY		: re
re			: fclean all ## Rebuild executables

.PHONY		: test
test		: $(NAME_STL) $(NAME_FT) ## Test std::vector and ft::vector
	$(TEST_SCRIPT)

.PHONY		: retest
retest		: fclean test ## Rebuild and test

.PHONY: help
help			: ## Show this message
	@echo "Target lists:"
	@grep -E '^[a-zA-Z_-]+\t*:.*?## .*$$' Makefile | awk 'BEGIN {FS = "\t*:.*?## "}; {printf "    \033[36m%-10s\033[0m %s\n", $$1, $$2}'
