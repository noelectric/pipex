CC = @cc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex

SRC = pipex.c pipex_utils.c ft_split.c pipex_utils1.c\

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

OBJ_DIR = ./obj

SRC_DIR = ./src

INC = include/pipex.h

all : $(NAME)

$(NAME) : $(OBJ)
		@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
		@echo "`tput setaf 2`Done for pipex"

$(OBJ_DIR) :
		@mkdir $(OBJ_DIR)

$(OBJ) : $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC) | $(OBJ_DIR)
		@$(CC) -c $< -o $@

clean :
		@rm -rf $(OBJ_DIR)

fclean : clean
		@rm -rf $(NAME)

re : fclean $(NAME)
