NAME			 = minishell

CC 				 = gcc
CCFLAGS			 = -Wall -Werror -Wextra -g -O0

SRC_FILES		 =	builtins.c		\
					dictionary.c	\
					environment.c	\
					errors.c		\
					main.c			\
					minishell.c		\
					path.c			\
					readline.c
					
					

OBJ_FILES		 = $(SRC_FILES:.c=.o)

SRC_DIR			 = srcs/
OBJ_DIR			 = obj/

SRC				 = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ				 = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

LIBFT_FILE		 = libft.a
LIBFT_DIR		 = libft/
LIBFT_FLAGS		 = -lft -L $(LIBFT_DIR)
LIBFT			 = $(addprefix $(LIBFT_DIR), $(LIBFT_FILE))
INC 			 = includes/

FLAGS			 = $(CCFLAGS) $(LIBFT_FLAGS)

MINISHELL_HEADER = minishell.h

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(FLAGS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC)$(MINISHELL_HEADER)
	$(CC) $(CCFLAGS) -I $(INC) -I $(LIBFT_DIR) -c $< -o $@ 

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all