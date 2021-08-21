NAME_STL:= tester_stl
NAME_FT	:= tester_ft

LOG_STL	:= result_stl.log
LOG_FT	:= result_ft.log

SRCS	:= tests/main.cpp tests/Foo.cpp tests/vector/test_vector_iterator.cpp
INC		:= -I./includes -I./tests

CXX		:= clang++
CXXFLAGS:= -Wall -Wextra -Werror -std=c++98 $(INC)

.PHONY	: all
all		: $(NAME_STL) $(NAME_FT)

$(NAME_STL)	: $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(NAME_STL) $(SRCS)

$(NAME_FT)	: $(SRCS)
	$(CXX) $(CXXFLAGS) -D IS_FT=1 -o $(NAME_FT) $(SRCS)

.PHONY		: fclean
fclean		:
	$(RM) $(NAME_STL) $(NAME_FT) $(LOG_STL) $(LOG_FT)

.PHONY		: re
re			: fclean all

.PHONY		: test
test		: $(NAME_STL) $(NAME_FT)
	$(RM) $(LOG_STL) $(LOG_FT)
	time ./$(NAME_STL) > result_stl.log
	time ./$(NAME_FT) > result_ft.log
	diff result_stl.log result_ft.log
