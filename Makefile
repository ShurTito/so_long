# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antferna <antferna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/05 15:36:04 by antferna          #+#    #+#              #
#    Updated: 2023/07/13 16:49:25 by antferna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

NAME_BONUS = so_long_bonus

SRC = src/so_long.c src/map.c src/check_map.c src/set_image.c src/player.c

OBJ = $(SRC:.c=.o)

SRC_BONUS = srcb/so_long_bonus.c srcb/map_bonus.c srcb/check_map_bonus.c srcb/set_image_bonus.c srcb/player_bonus.c srcb/mob_bonus.c

OBJ_BONUS = $(SRC_BONUS:.c=.o)

MLX_PATH = ./MLX42

MLX = $(MLX_PATH)/libmlx42.a

LIBFT_PATH = ./libft

LIBFT = $(LIBFT_PATH)/libft.a

SO_LONG = so_long.a

SO_LONG_BONUS = so_long_bonus.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LIB = ar rcs

LIB_SYS = -Iinclude -lglfw -L "/Users/antferna/.brew/opt/glfw/lib/" 

RM = rm -fr

$(NAME):		$(OBJ) $(LIBFT) $(MLX)
				@$(LIB) $(SO_LONG) $(OBJ)
				@$(CC) $(CFLAGS) $(SO_LONG) $(MLX) $(LIBFT) $(LIB_SYS) -o $(NAME)

$(NAME_BONUS): 	$(OBJ_BONUS) $(LIBFT) $(MLX)
				$(LIB) $(SO_LONG_BONUS) $(OBJ_BONUS)
				$(CC) $(CFLAGS) $(SO_LONG_BONUS) $(MLX) $(LIBFT) $(LIB_SYS) -o $(NAME_BONUS)

$(OBJ):			src/%.o : src/%.c 
				$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_BONUS):	srcb/%.o : srcb/%.c 
				$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
				@make -s -C $(LIBFT_PATH)

$(MLX):
				@make -s -C $(MLX_PATH)

all: 			$(NAME)

bonus:			$(NAME_BONUS)

clean:
				$(RM) $(OBJ) $(OBJ_BONUS)
				make clean -s -C $(MLX_PATH)
				make clean -s -C $(LIBFT_PATH)

fclean:
				$(RM) $(NAME_BONUS) $(NAME) $(OBJ) $(OBJ_BONUS) $(SO_LONG) $(SO_LONG_BONUS) $(LIBFT) $(MLX)
				make fclean -s -C $(MLX_PATH)
				make fclean -s -C $(LIBFT_PATH)

re: 			fclean all

solong: 		all clean

solongb: 		bonus clean

.PHONY: all re clean fclean bonus solong solongb

#gcc -Wall -Wextra -Werror so_long.c libft/libft.a MLX42/libmlx42.a -Iinclude -lglfw -L"/Users/$USER/.brew/opt/glfw/lib/"