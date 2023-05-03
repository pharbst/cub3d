# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlohmann <jlohmann@student.42heilbronn.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/01 16:05:35 by jlohmann          #+#    #+#              #
#    Updated: 2023/05/03 04:01:10 by jlohmann         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# **************************************************************************** #
# Operating System tracking
# **************************************************************************** #
UNAME		=	$(shell uname)
OS			=	$(shell cat /etc/os-release | grep -e NAME | cut -d= -f2 | tr -d '"')
OS_LIKE		=	$(shell cat /etc/os-release | grep ID_LIKE | cut -d= -f2)


# ****************************************************************************  #
# Colors and Printing stuff
# ****************************************************************************  #
RESET  = \033[01;00m
RED    = \033[01;31m
GREEN  = \033[01;32m
YELLOW = \033[01;33m
BLUE   = \033[01;34m

# ---------------------------------------------------------------------------- #

NAME	:= cub3D

CC		:= cc
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
#CFLAGS	:=	-Wall -Werror -Wextra -Wunreachable-code -g
# CFLAGS	+=	-fsanitize=address

LIBFT	:= ./lib/libft
LIBMLX	:= ./lib/MLX42
HEADER	:= ./inc/cub3d.h ./inc/cub3d_structs.h ./inc/cub3d_error.h ./inc/graphics.h

HEADERS	:= -I ./inc -I $(LIBFT)/inc -I $(LIBMLX)/include -I $(LIBMLX)/src/font
ifeq ($(UNAME), Darwin)
LIBS	:= $(LIBFT)/libft.a $(LIBMLX)/build/libmlx42.a -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -lm -framework Cocoa -framework OpenGL -framework IOKit
else
LIBS	:= $(LIBFT)/libft.a $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
endif
VPATH	:= src src/parsing src/rendering src/scene src/utils
SRCS	:= main.c hooks.c
# Parsing
SRCS	+=	check_map_utils.c \
			check_map.c \
			error.c \
			get_map.c \
			get_textures.c \
			parsing_main.c \
			parsing_utils.c
# Rendering
SRCS	+=	draw_cubes.c fps_counter.c raycaster.c
# Scene
SRCS	+=	map.c player.c scene.c
# Utils
SRCS	+=	color_utils.c common_utils.c draw_utils.c error_handling.c init_utils.c

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

$(ODIR)/%.o : %.c $(HEADER) | $(ODIR)
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
