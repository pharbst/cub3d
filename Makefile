# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/01 16:05:35 by jlohmann          #+#    #+#              #
#    Updated: 2023/05/03 12:41:57 by pharbst          ###   ########.fr        #
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
Black			=	$(shell echo "\033[0;30m")
FBlack			=	$(shell echo "\033[1;30m")
Red				=	$(shell echo "\033[0;31m")
FRed			=	$(shell echo "\033[1;31m")
BRed			=	$(shell echo "\033[1;41m")
Green			=	$(shell echo "\033[0;32m")
FGreen			=	$(shell echo "\033[1;32m")
Brown/Orange	=	$(shell echo "\033[0;33m")
FBrown/Orange	=	$(shell echo "\033[1;33m")
FYellow			=	$(shell echo "\033[1;33m")
Yellow			=	$(shell echo "\033[0;33m")
Blue			=	$(shell echo "\033[0;34m")
FBlue			=	$(shell echo "\033[1;34m")
Purple			=	$(shell echo "\033[0;35m")
FPurple			=	$(shell echo "\033[1;35m")
Cyan			=	$(shell echo "\033[0;36m")
FCyan			=	$(shell echo "\033[1;36m")
FWhite			=	$(shell echo "\033[1;37m")
White			=	$(shell echo "\033[0;37m")
RESET			=	$(shell echo "\033[0m")
TICK			=	$(shell echo "\xE2\x9C\x94")
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

all:
	@printf "%-50s$(RESET)" "$(FYellow)Compiling libft ..."
	@$(MAKE) -j -C $(LIBFT) >/dev/null
	@printf "$(FGreen)✔\n$(RESET)"
	@printf "%-50s$(RESET)" "$(FYellow)Compiling libmlx ..."
	@$(MAKE) libmlx >/dev/null
	@printf "$(FGreen)✔\n$(RESET)"
	@printf "\n\n$(FYellow)Compiling cub3D:\n$(RESET)"
	@$(MAKE) $(NAME)

libft:
	@$(MAKE) -j -C $(LIBFT) $(MAKECMDGOALS)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	@printf "$(GREEN)Done$(RESET)\n"

$(ODIR)/%.o : %.c $(HEADER) | $(ODIR)
	@printf "%-50s$(RESET)" "$(Yellow)Compiling $< ..."
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@printf "$(FGreen)✔\n$(RESET)"

$(ODIR):
	@mkdir -p $@

# ---------------------------------------------------------------------------- #

clean: libft
	@printf "%-50s$(RESET)" "$(FRed)Cleaning up ..."
	@$(RM) -rf $(ODIR)
	@$(RM) -rf $(LIBMLX)/build
	@printf "$(FGreen)✔\n$(RESET)"

fclean: libft
	@printf "%-50s$(RESET)" "$(FRed)FCleaning up ..."
	@$(RM) -rf $(ODIR)
	@$(RM) -rf $(LIBMLX)/build
	@printf "$(FGreen)✔\n$(RESET)"
	@rm -f $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re libft libmlx
