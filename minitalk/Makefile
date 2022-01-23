NAME = server
NAME2 = client
SRC = ft_server.c 
SRC2 = ft_client.c


HEADER = minitalk.h
CC = gcc

FLAGS = -Wall -Wextra -Werror

all: $(NAME) $(NAME2)

$(NAME): $(HEADER) $(SRC) Makefile
	${CC} ${FLAGS} $(SRC) -o $(NAME)
$(NAME2): $(HEADER) $(SRC2) Makefile
	${CC} ${FLAGS} $(SRC2) -o $(NAME2)
clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAME2)

re: fclean all

.PHONY : all clean fclean re 
