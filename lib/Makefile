# -*- MakeFile -*-

CC = @cc

CFLAGS = -Wall -Wextra -Werror

NAME = lib.a

SRC =	

OBJ = $(SRC:.c=.o)

MSG1 = @echo "\e[1;32m Compiled ${NAME} Successfully ✔︎ \e[0m"
MSG2 = @echo "\033[93m Cleaned ${NAME} Successfully ✔︎ \e[0m"

all: $(NAME)

$(NAME): $(OBJ)
	@ar -rcs $(NAME) $(OBJ)
	$(MSG1)

clean:
	@/bin/rm -rf $(OBJ)
	$(MSG2)

fclean: clean
	@/bin/rm -rf $(NAME)
#	$(MSG2)

re: fclean all