NAME				= cub3D
CC					= cc
CFLAGS				= -Wall -Wextra -Werror -I$(LIBFT_DIR) -I$(LIBMLX_DIR) -I$(INCLUDE_DIR)
CFLAGS_LIB			= -lft -L $(LIBFT_DIR) -lmlx -L $(LIBMLX_DIR) -lXext -lX11 -lm -lz

INCLUDE_DIR			= include
INCLUDE_FILES		= include/cub3d.h include/constants.h
SRC_DIR				= src
OBJ_DIR				= obj
LIB_DIR				= lib
LIBFT_DIR			= lib/libft
LIBMLX_DIR			= lib/libmlx

SRC_FILES			= src/draw/draw_walls.c
SRC_FILES			+= src/draw/draw_pixel.c
SRC_FILES			+= src/setup/init.c
SRC_FILES			+= src/setup/hooks_setup.c
SRC_FILES			+= src/update/render.c
SRC_FILES			+= src/update/update_player.c
SRC_FILES			+= src/update/update.c
SRC_FILES			+= src/utils/get_color_value.c
SRC_FILES			+= src/utils/free_split.c
SRC_FILES			+= src/parse/get_map_data.c
SRC_FILES			+= src/parse/trimm_line.c
SRC_FILES			+= src/parse/get_assets.c
SRC_FILES			+= src/parse/is_map.c
SRC_FILES			+= src/parse/parse.c
SRC_FILES			+= src/parse/is_cardinal.c
SRC_FILES			+= src/parse/handle_grid.c
SRC_FILES			+= src/parse/is_entry.c
SRC_FILES			+= src/parse/get_player_start.c
SRC_FILES			+= src/parse/create_data.c
SRC_FILES			+= src/parse/is_rgb_line.c
SRC_FILES			+= src/parse/get_size.c
SRC_FILES			+= src/parse/get_grid.c
SRC_FILES			+= src/raycast/ray.c
SRC_FILES			+= src/raycast/dda.c
SRC_FILES			+= src/raycast/raycast.c
SRC_FILES			+= src/input/input.c
SRC_FILES			+= src/input/exit.c
SRC_FILES			+= src/check_map/check_wall.c

OBJ_FILES			= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
MAIN				= main.c
VALGRIND			= valgrind --leak-check=full --show-leak-kinds=all
VALGRIND			+= --track-origins=yes --quiet --tool=memcheck

# ********** BONUS ********** #

INCLUDE_BONUS_DIR	= include_bonus
INCLUDE_BONUS_FILES	= include_bonus/cub3d_bonus.h include_bonus/constants_bonus.h
SRC_BONUS_DIR		= src_bonus
OBJ_BONUS_DIR		= obj_bonus

CFLAGS_BONUS		= -Wall -Wextra -Werror -I$(LIBFT_DIR) -I$(LIBMLX_DIR) -I$(INCLUDE_BONUS_DIR)

SRC_BONUS_FILES		= src_bonus/draw/draw_walls_bonus.c
SRC_BONUS_FILES		+= src_bonus/draw/draw_pixel_bonus.c
SRC_BONUS_FILES		+= src_bonus/setup/init_bonus.c
SRC_BONUS_FILES		+= src_bonus/setup/hooks_setup_bonus.c
SRC_BONUS_FILES		+= src_bonus/update/render_bonus.c
SRC_BONUS_FILES		+= src_bonus/update/update_player_bonus.c
SRC_BONUS_FILES		+= src_bonus/update/update_bonus.c
SRC_BONUS_FILES		+= src_bonus/utils/free_split_bonus.c
SRC_BONUS_FILES		+= src_bonus/utils/get_color_value_bonus.c
SRC_BONUS_FILES		+= src_bonus/parse/is_entry_bonus.c
SRC_BONUS_FILES		+= src_bonus/parse/is_cardinal_bonus.c
SRC_BONUS_FILES		+= src_bonus/parse/parse_bonus.c
SRC_BONUS_FILES		+= src_bonus/parse/get_assets_bonus.c
SRC_BONUS_FILES		+= src_bonus/parse/create_data_bonus.c
SRC_BONUS_FILES		+= src_bonus/parse/get_player_start_bonus.c
SRC_BONUS_FILES		+= src_bonus/parse/is_rgb_line_bonus.c
SRC_BONUS_FILES		+= src_bonus/parse/get_grid_bonus.c
SRC_BONUS_FILES		+= src_bonus/parse/handle_grid_bonus.c
SRC_BONUS_FILES		+= src_bonus/parse/trimm_line_bonus.c
SRC_BONUS_FILES		+= src_bonus/parse/is_map_bonus.c
SRC_BONUS_FILES		+= src_bonus/parse/get_map_data_bonus.c
SRC_BONUS_FILES		+= src_bonus/parse/get_size_bonus.c
SRC_BONUS_FILES		+= src_bonus/raycast/dda_bonus.c
SRC_BONUS_FILES		+= src_bonus/raycast/ray_bonus.c
SRC_BONUS_FILES		+= src_bonus/raycast/raycast_bonus.c
SRC_BONUS_FILES		+= src_bonus/input/input_bonus.c
SRC_BONUS_FILES		+= src_bonus/input/exit_bonus.c
SRC_BONUS_FILES		+= src_bonus/check_map/check_wall_bonus.c

OBJ_BONUS_FILES		= $(patsubst $(SRC_BONUS_DIR)/%.c, $(OBJ_BONUS_DIR)/%.o, $(SRC_BONUS_FILES))
MAIN_BONUS			= main_bonus.c

# ********** RULES ********** #

all:				$(NAME)

$(NAME):			$(MAIN) $(OBJ_DIR) $(OBJ_FILES) $(INCLUDE_FILES)
					$(MAKE) -C $(LIBFT_DIR)
					$(MAKE) -C $(LIBMLX_DIR)
					$(CC) $(MAIN) $(OBJ_FILES) $(CFLAGS) $(CFLAGS_LIB) \
						-o $(NAME)

$(OBJ_DIR):
					mkdir -p $@

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c
					mkdir -p "$(@D)"
					$(CC) -c $< $(CFLAGS) -o $@

bonus:				$(MAIN_BONUS) $(OBJ_BONUS_DIR) $(OBJ_BONUS_FILES) $(INCLUDE_BONUS_FILES)
					$(MAKE) -C $(LIBFT_DIR)
					$(MAKE) -C $(LIBMLX_DIR)
					$(CC) $(MAIN_BONUS) $(OBJ_BONUS_FILES) $(CFLAGS_BONUS) $(CFLAGS_LIB) \
						-o $(NAME)_bonus
					
$(OBJ_BONUS_DIR):
					mkdir -p $@

$(OBJ_BONUS_DIR)/%.o:	$(SRC_BONUS_DIR)/%.c
						mkdir -p "$(@D)"
						$(CC) -c $< $(CFLAGS_BONUS) -o $@

clean:
					echo $(CLEANING_MSG)
					rm -rf $(OBJ_DIR)
					rm -rf $(OBJ_BONUS_DIR)
					rm -rf debug
					rm -rf new_core*
					$(MAKE) -C $(LIBFT_DIR) clean
					$(MAKE) -C $(LIBMLX_DIR) clean

fclean:				clean
					rm -f $(NAME)
					rm -f $(NAME)_bonus
					$(MAKE) -C $(LIBFT_DIR) fclean
					$(MAKE) -C $(LIBMLX_DIR) clean

re:					fclean all

re_bonus:			fclean bonus

# Add -g flag and change output to debug
setup_debug:
					$(eval NAME=debug)
					$(eval CFLAGS+=-g)

# Compile with -g flag and output the 'debug' file
debug:				clean setup_debug all

run:				all
					@./$(NAME) ./map/simple.cub

runv:				debug
					@$(VALGRIND) ./debug ./map/simple.cub

test:				all
					./tests/tests.sh

.PHONY:	all run clean fclean re re_bonus debug setup_debug
