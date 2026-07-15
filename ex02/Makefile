CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
SRCS = generate.cpp indentify.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)
NAME = indentify

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