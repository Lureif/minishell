# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brjorgen <brjorgen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/10 00:40:57 by brjorgen          #+#    #+#              #
#    Updated: 2019/11/18 20:34:24 by brjorgen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=			 minishell

SRC			    =			environement_functions.c \
							ft_builtins.c \
							ft_process_launch.c \
							ft_shell_utils.c \
							get_next_line.c \
							main.c \
							print_welcome_banner.c \
							tab_functions.c

CC			= 		       	   gcc
FLG			= 	 -Wall -Werror -Wextra -g3  #-fsanitize=address
LIB			= 	       -L ./libft -lft
INC			=		     -I libft/
OBJ			= 		  $(SRC:.c=.o)

all			: $(NAME)

libft/libft.a:
			cd libft && make

$(NAME)			:$(OBJ) libft/libft.a
				gcc $(OBJ) $(FLG) $(LIB) -o $(NAME)

%.o			: %.c $(HEADERS)
				gcc $(INC) $(FLG) -c $< -o $@

clean:
			rm -rf $(OBJ)
			cd libft && make clean

fclean: 		clean
			rm -rf $(NAME)
			cd libft && make fclean

re: fclean all
