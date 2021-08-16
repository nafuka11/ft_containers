NAME	:= tester

SRCS	:= tests/main.cpp
OBJS	:= $(SRCS:.cpp=.o)
INC		:= -I./includes

CXX		:= clang++
CXXFLAGS:= -Wall -Wextra -Werror -std=c++98 $(INC)

.PHONY	: all
all		: $(NAME)

$(NAME)	: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

.PHONY	: clean
clean	:
	$(RM) $(OBJS)

.PHONY	: fclean
fclean	: clean
	$(RM) $(NAME)

.PHONY	: re
re		: fclean all
