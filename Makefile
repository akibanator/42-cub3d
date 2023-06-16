NAME				= cub3D
CC					= gcc

MINILIBX_DIR		= ./minilibx-linux

all:				libft

libft:
					@$(MAKE) -C $(MINILIBX_DIR)

clean:				
					@$(MAKE) -C $(MINILIBX_DIR) clean

#fclean:				

#re

.PHONY: all clean fclean re