NAME = minishell

CC = cc

CFLAGS = -g -Wall -Wextra -Werror -I includes

INCLUDE = -I include/

HEADER = minishell.h

MAIN = main.c map_checker.c

GNL = get_net_line get_next_line_utils

SRC = $(addsuffix .c, $(addprefix srcs/main/, $(MAIN))) \

	  

OBJ = $(SRC:c=o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[0;32mCub3d compiled"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lreadline
	@echo "\n\033[0m./minishell to execute the program !"

%.o: %.c
	@printf "\033[0;33mGenerating minishell objects... %-33.33s\r\n" $@
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@echo "\nRemoving binaries..."
	@rm -f $(OBJ)
	@echo "\033[0m"

fclean:
	@echo "\nDeleting objects..."
	@rm -f $(OBJ)
	@echo "\nDeleting executable..."
	@rm -f $(NAME)
	@echo "\033[0m"

re: fclean all


.PHONY: clean fclean re 