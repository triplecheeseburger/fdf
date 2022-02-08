# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/19 19:37:01 by hakim             #+#    #+#              #
#    Updated: 2022/02/09 03:52:02 by hakim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -lmlx -framework OpenGL -framework Appkit

NAME = fdf
BONUS_NAME = fdf
SRCS =	srcs/color.c \
		srcs/drawing.c \
		srcs/drawing_utils.c \
		srcs/fdf.c \
		srcs/get_next_line.c \
		srcs/get_next_line_utils.c \
		srcs/input_handler.c \
		srcs/parse.c \
		srcs/parse_color.c \
		srcs/prepare.c \
		srcs/projection.c \
		srcs/utils_free.c \
		srcs/xiaolin_wu.c
BONUS_SRCS = bonus_bonus.color_bonus.c \
			 bonus/drawing_bonus.c \
			 bonus/drawing_utils_bonus.c \
			 bonus/fdf_bonus.c \
			 bonus/get_next_line_bonus.c \
			 bonus/get_next_line_utils_bonus.c \
			 bonus/input_handler_bonus.c \
			 bonus/parse_bonus.c \
			 bonus/parse_bonus.color_bonus.c \
			 bonus/prepare_bonus.c \
			 bonus/proj_bonus.ction_bonus.c \
			 bonus/utils_free_bonus.c \
			 bonus/xiaolin_wu_bonus.c
OBJS = $(SRCS:%.c=%.o)
BONUS_OBJS = $(BONUS_SRCS:%.c=%.o)
HDR = ./includes
BONUS_HDR= ./bonus_includes

LIB_DIR = ./libft
LIB_NAME = ft
LIB = $(LIB_DIR)/lib$(LIB_NAME).a

INCLUDES = -I$(HDR) -I$(LIB_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME):$(LIB) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -L$(LIB_DIR) -l$(LIB_NAME) $(OBJS) -o $(NAME)

$(LIB):
	make -C $(LIB_DIR) bonus

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(LIB) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -L$(LIB_DIR) -l$(LIB_NAME) $(BONUS_OBJS) -o $(BONUS_NAME)

clean:
	rm -f $(OBJS) $(BONUS_OBJS)
	make -C $(LIB_DIR) clean

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	make -C $(LIB_DIR) fclean

re: fclean all

.PHONY: fclean all clean re bonus
