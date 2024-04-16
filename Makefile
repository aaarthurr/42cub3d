NAME = minishell

CC = cc

CFLAGS = -g -Wall -Wextra -Werror -I includes

HEADER = minishell.h

BUILTINS = pwd cd export env unset echo

ENV = handle_variable export_utils

EXEC = exec exit

MAIN = main manager signal redirections

PARSING = init_data init_data_utils

TOOLS = free_utils libutils ft_split_enhanced tools

PIPEX = ft_exec_cmd pipex utils find_path

SRC = $(addsuffix .c, $(addprefix srcs/main/, $(MAIN))) \
	$(addsuffix .c, $(addprefix srcs/tools/, $(TOOLS))) \
	$(addsuffix .c, $(addprefix srcs/builtins/, $(BUILTINS))) \
	$(addsuffix .c, $(addprefix srcs/exec/, $(EXEC))) \
	$(addsuffix .c, $(addprefix srcs/env/, $(ENV))) \
	$(addsuffix .c, $(addprefix srcs/pipex/, $(PIPEX))) \
	$(addsuffix .c, $(addprefix srcs/parsing/, $(PARSING))) \
	  

OBJ = $(SRC:c=o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[0;32mMinishell Compiled !"
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