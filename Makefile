# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/01 16:05:35 by jlohmann          #+#    #+#              #
#    Updated: 2023/04/14 02:32:43 by pharbst          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RESET  = \033[01;00m
RED    = \033[01;31m
GREEN  = \033[01;32m
YELLOW = \033[01;33m
BLUE   = \033[01;34m

# ---------------------------------------------------------------------------- #

NAME	:= cub3D

CC		:= cc
#CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -g

LIBFT	:= ./lib/libft
LIBMLX	:= ./lib/MLX42

HEADERS	:= -I ./inc -I $(LIBFT)/inc -I $(LIBMLX)/include
# LIBS	:= $(LIBFT)/libft.a $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
LIBS	:= $(LIBFT)/libft.a $(LIBMLX)/build/libmlx42.a -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -lm -framework Cocoa -framework OpenGL -framework IOKit

VPATH	:= src src/graphics src/parsing
SRCS	:= common_utils.c hooks.c main.c player.c raycaster.c color_utils.c draw_utils.c init_utils.c map.c scene.c error_handling.c input.c player_utils.c
# Parsing
SRCS	+=	check_map_utils.c \
			check_map.c \
			error.c \
			get_map.c \
			get_textures.c \
			parse_map.c \
			parsing_main.c \
			parsing_utils.c \
			tex_init.c \

ODIR	:= obj
OBJS = $(SRCS:%.c=$(ODIR)/%.o)

# ---------------------------------------------------------------------------- #

all: libmlx libft $(NAME)

libft:
	@$(MAKE) -C $(LIBFT) $(MAKECMDGOALS)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	@printf "$(GREEN)Done$(RESET)\n"

$(ODIR)/%.o : %.c ./inc/cub3d.h ./inc/graphics.h | $(ODIR)
	@printf "Compiling $< ... "
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@printf "✔\n"

$(ODIR):
	mkdir -p $@

# ---------------------------------------------------------------------------- #

clean: libft
	@printf "$(RED)Cleaning up ... $(RESET)"
	@$(RM) -rf $(ODIR)
	@$(RM) -rf $(LIBMLX)/build
	@printf "✔\n"

fclean: clean
	@rm -f $(NAME)

re: clean all

.PHONY: all clean fclean re libft libmlx
