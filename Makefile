NAME_STL:= tester_stl
NAME_FT	:= tester_ft

LOG_STL	:= result_stl.log
LOG_FT	:= result_ft.log

SRCS	:= tests/main.cpp tests/common.cpp tests/Foo.cpp \
		   tests/vector/test_vector.cpp \
		   tests/map/test_map.cpp tests/map/PairTester.cpp
INC		:= -I./includes -I./tests

CXX		:= clang++
CXXFLAGS:= -Wall -Wextra -Werror -std=c++98 $(INC)

.PHONY	: all
all		: $(NAME_STL) $(NAME_FT) ## Build executables

$(NAME_STL)	: $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(NAME_STL) $(SRCS)

$(NAME_FT)	: $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(NAME_FT) -D IS_FT=1 $(SRCS)

.PHONY		: fclean
fclean		: ## Delete executables and logs
	$(RM) $(NAME_STL) $(NAME_FT) $(LOG_STL) $(LOG_FT)

.PHONY		: re
re			: fclean all ## Rebuild executables

.PHONY		: test
test		: $(NAME_STL) $(NAME_FT) ## Test std::vector and ft::vector
	$(RM) $(LOG_STL) $(LOG_FT)
	time ./$(NAME_STL) > result_stl.log
	time ./$(NAME_FT) > result_ft.log
	diff result_stl.log result_ft.log

.PHONY		: retest
retest		: fclean test ## Rebuild and test

.PHONY: help
help			: ## Show this message
	@echo "Target lists:"
	@grep -E '^[a-zA-Z_-]+\t*:.*?## .*$$' Makefile | awk 'BEGIN {FS = "\t*:.*?## "}; {printf "    \033[36m%-10s\033[0m %s\n", $$1, $$2}'
