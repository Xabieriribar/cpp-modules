FLAGS = -Wall -Wextra -Werror -std=c++98
CC = c++
NAME = global_banksters
SRC = Account.cpp \
	tests.cpp

OBJECT = Account.o \
			tests.o

all: $(NAME)

$(NAME): $(OBJECT)
	$(CC) $(FLAGS) $(OBJECT) -o $(NAME)

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJECT)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all fclean clean re