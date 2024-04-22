NAME = cub3d

CC = cc

CFLAGS = -g -Wall -Wextra -Werror -I includes

INCLUDE = -I include/

HEADER = cubed.h

MAIN = main map_checker mapping

GNL = get_next_line get_next_line_utils

SRC = 	$(addsuffix .c, $(addprefix src/main/, $(MAIN))) \
		$(addsuffix .c, $(addprefix src/get_next_line/, $(GNL))) \

	  

OBJ = $(SRC:c=o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[0;32mCub3d compiled"
	@$(CC) $(CFLAGS) $(OBJ) -o $@
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