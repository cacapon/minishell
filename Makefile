# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/03 12:55:20 by ttsubo            #+#    #+#              #
#    Updated: 2025/04/05 13:45:55 by ttsubo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc

SRC_DIR = src/
INC_DIR = inc/
OBJ_DIR = obj/

MAKEFLAGS += --no-print-directory
W_FLG = -Wall -Wextra -Werror
I_FLG = -I$(INC_DIR)
L_FLG = -lreadline

SRC = main.c minish_signal.c

SRCS = $(addprefix $(SRC_DIR), $(SRC))
OBJS = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(W_FLG) $(L_FLG) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(W_FLG) $(I_FLG) -c $< -o $@ 

clean:
	rm -rf $(OBJ_DIR)*.o

fclean:
	$(MAKE) clean
	rm -rf $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re