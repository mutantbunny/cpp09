CC = c++
CFLAGS = -Wall -Wextra -Werror -O3 -ggdb -std=c++98
RM = rm -f

NAME = PmergeMe

SRCS = main.cpp PmergeMe.cpp

OBJS = $(SRCS:.cpp=.o)

INCS = PmergeMe.hpp

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
	valgrind --leak-check=full ./$(NAME) `shuf -i 1-100000 -n 3000 | tr "\n" " "`

re: fclean all

.PHONY: all clean fclean leaks re
