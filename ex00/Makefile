CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
SRCS = ScalarConverter.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)
NAME = ScalarConverter

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re