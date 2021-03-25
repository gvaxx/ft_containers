SHELL = /bin/sh

CC = clang++
RM = rm -rf
FLAGS = --std=c++98

NAME = containers
SRC = main.cpp
OBJ = $(SRC:.cpp=.o)
HDRS = *.hpp
all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) $(FLAGS)
	
%.o: %.cpp $(HDRS)
	@$(CC) -c $< -o $@ $(FLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test: all
	./$(NAME)
retest: re test
.PHONY: all clean fclean re
