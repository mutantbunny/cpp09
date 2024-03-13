CC = c++
CFLAGS = -Wall -Wextra -Werror -O3 -ggdb -std=c++98
RM = rm -f

NAME = PmergeMe

SRCS = main.cpp PmergeMe.cpp utils.cpp

OBJS = $(SRCS:.cpp=.o)

INCS = PmergeMe.hpp utils.hpp

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp $(INCS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

leaks: $(NAME)
	valgrind --leak-check=full ./$(NAME)

re: fclean all

.PHONY: all clean fclean leaks re
