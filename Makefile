# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pharbst <pharbst@student.42heilbronn.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/01 16:05:35 by jlohmann          #+#    #+#              #
#    Updated: 2023/05/03 20:11:20 by pharbst          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# **************************************************************************** #
# Operating System tracking
# **************************************************************************** #
UNAME		=	$(shell uname)
OS			=	$(shell cat /etc/os-release | grep -e NAME | cut -d= -f2 | tr -d '"')
OS_LIKE		=	$(shell cat /etc/os-release | grep ID_LIKE | cut -d= -f2)


include color.mk

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
	@$(MAKE) -s proname_header
	@$(MAKE) -s std_all
	
	

std_all:
	@printf "%-79s$(RESET)" "$(Yellow)Compiling $(FCyan)libft ..."
	@$(MAKE) -j -s -C $(LIBFT) >/dev/null
	@printf "$(FGreen)[$(TICK)]\n$(RESET)"
	@printf "%-79s$(RESET)" "$(Yellow)Compiling $(FCyan)libmlx ..."
	@$(MAKE) -s libmlx >/dev/null
	@printf "$(FGreen)[$(TICK)]\n$(RESET)"
	@printf "\n\n%-81s\n$(RESET)" "$(Yellow)Compiling $(FBlue)cub$(FYellow)3D :("
	@$(MAKE) -s $(NAME)
	@printf "$(SETCURUP)"
	@printf "%-86s$(RESET)" "$(Yellow)Compiling $(FBlue)cub$(FYellow)3D :)"
# @printf "%-95s$(RESET)" "$(Yellow)Compiling $(FBlue)cub$(FYellow)3D $(FGreen)$(SCHMILI)"
	@printf "$(FGreen)$(TICKBOX)\n$(RESET)"

libft:
	@$(MAKE) -j -s -C $(LIBFT) $(MAKECMDGOALS) >/dev/null

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -s -C $(LIBMLX)/build -j

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

$(ODIR)/%.o : %.c $(HEADER) | $(ODIR)
	@printf "%-50s$(RESET)\r" "$(Green)Compiling $< ..."
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(ODIR):
	@mkdir -p $@

# ---------------------------------------------------------------------------- #

clean: libft
	@printf "%-50s$(RESET)" "$(FRed)Cleaning up ..."
	@$(RM) -rf $(ODIR)
	@$(RM) -rf $(LIBMLX)/build
	@printf "$(FGreen)$(TICKBOX)\n$(RESET)"

fclean: libft
	@printf "%-72s$(RESET)" "$(FPurple)FCleaning up ..."
	@$(RM) -rf $(ODIR)
	@$(RM) -rf $(LIBMLX)/build
	@printf "$(FGreen)$(TICKBOX)\n$(RESET)"
	@rm -f $(NAME)

re:
	@$(MAKE) -s proname_header
	@$(MAKE) -s fclean
	@$(MAKE) -s std_all

proname_header:
	@printf "$(FRed)╔══════════════════════════════════════════════════════════════════╗\n\
$(FRed)║        $(FBlue)                     /██      $(FYellow)  /██████  /███████         $(FRed)║\n\
$(FRed)║        $(FBlue)                    | ██      $(FYellow) /██__  ██| ██__  ██        $(FRed)║\n\
$(FRed)║        $(FBlue)  /███████ /██   /██| ███████ $(FYellow)|__/  \\ ██| ██  \\ ██        $(FRed)║\n\
$(FRed)║        $(FBlue) /██_____/| ██  | ██| ██__  ██$(FYellow)   /█████/| ██  | ██        $(FRed)║\n\
$(FRed)║        $(FBlue)| ██      | ██  | ██| ██  \\ ██$(FYellow)  |___  ██| ██  | ██        $(FRed)║\n\
$(FRed)║        $(FBlue)| ██      | ██  | ██| ██  | ██$(FYellow) /██  \\ ██| ██  | ██        $(FRed)║\n\
$(FRed)║        $(FBlue)|  ███████|  ██████/| ███████/$(FYellow)|  ██████/| ███████/        $(FRed)║\n\
$(FRed)║        $(FBlue) \\_______/ \\______/ |_______/ $(FYellow) \\______/ |_______/         $(FRed)║\n\
╚══════════════════════════════════════════════════════════════════╝\n$(RESET)"

.PHONY: all clean fclean re libft libmlx proname_header std_all
