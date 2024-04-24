NAME = cub3d

CC = cc

CFLAGS = -g -Wall -Wextra -Werror -I includes

MLXFLAGS = -Lminilibx -lmlx -lXext -lX11

LIBPATH = minilibx

HEADER = cub3d.h

MAIN = main init checker game_manager error

RAYCASTING = raycasting

UTILS = tools tools_bis ft_tools free_manager

MAP = map_checker mapping

GNL = get_next_line get_next_line_utils

SRC = $(addsuffix .c, $(addprefix srcs/main/, $(MAIN))) \
	$(addsuffix .c, $(addprefix srcs/get_next_line/, $(GNL))) \
	$(addsuffix .c, $(addprefix srcs/utils/, $(UTILS))) \
	$(addsuffix .c, $(addprefix srcs/map/, $(MAP))) \
	#$(addsuffix .c, $(addprefix srcs/raycasting/, $(RAYCASTING))) \
	#$(addsuffix .c, $(addprefix srcs/pipex/, $(PIPEX))) \
	#$(addsuffix .c, $(addprefix srcs/parsing/, $(PARSING))) \
	  

OBJ = $(SRC:c=o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[0;32mMinilibx Compiled !"
	make -sC $(LIBPATH)
	@echo "\033[0;32mCub3d Compiled !"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -I. $(OBJS) $(MLXFLAGS) 
	@echo "\n\033[0m./cub3d to execute the program !"

%.o: %.c
	@printf "\033[0;33mGenerating Cub3d objects... %-33.33s\r\n" $@
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