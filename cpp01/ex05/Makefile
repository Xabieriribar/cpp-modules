FLAGS = -Wall -Wextra -Werror -std=c++98 -g3
CC = c++
NAME = Harl
SRC = $(wildcard *.cpp)
OBJECT = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJECT)
	$(CC) $(FLAGS) $(OBJECT) -o $(NAME)

clean:
	rm -f $(OBJECT)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY = all fclean clean re