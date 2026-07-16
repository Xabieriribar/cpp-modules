CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g3
CXX = c++
NAME = ScalarConverter
SRC = $(wildcard *.cpp)
OBJECT = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJECT)
	$(CXX) $(CXXFLAGS) $(OBJECT) -o $(NAME)

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECT)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all fclean clean re