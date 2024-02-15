
CXX = clang++
CFLAGS = -std=c++98 -Wall  -Wextra -g

SRCS := $(shell find . -name "*.cpp")

OBJS := $(SRCS:%.cpp=%.o)

# Target executable
NAME = webserver

# Main target
$(NAME): $(OBJS)
	$(CXX) $(CFLAGS) -o $(NAME) $(OBJS)

# Compile source files
%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@


.PHONY: clean fclean re start

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

start: re
	./$(NAME)