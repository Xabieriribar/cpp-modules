FLAGS = -Wall -Wextra -Werror -std=c++98
CC = c++
NAME = megaphone
SRC = megaphone.cpp
OBJECT = megaphone.o

all: $(NAME)

$(NAME): $(OBJECT)
	$(CC) $(FLAGS) $(OBJECT) -o $(NAME)

$(OBJECT) : $(SRC)
	$(CC) $(FLAGS) -c $(SRC) -o $(OBJECT)

clean:
	rm -f $(OBJECT)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY = all fclean clean re