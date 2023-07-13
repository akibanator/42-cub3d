#include "cub3d.h"
#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>

static char **map_copy(char *map, char **file) {
  int fd;
  char *line;
  char **head_file;
  fd = open(map, O_RDONLY);
  head_file = file;
  if (fd < 0) {
    printf("Map data not found in file [%s]\n", map);
    *file = NULL;
    return (head_file);
  }
  line = ft_get_next_line(fd);
  while (line != NULL) {
    *file = ft_strdup(line);
    free(line);
    line = ft_get_next_line(fd);
    file++;
  }
  return (head_file);
}

static int handle_struct_data(char **file, int nbr_lines, t_args *args) {
  while (nbr_lines--) {
    if (handle_cardinal(*file, "NO ", args, 0))
      return (1);
    else if (handle_cardinal(*file, "SO ", args, 1))
      return (1);
    else if (handle_cardinal(*file, "WE ", args, 2))
      return (1);
    else if (handle_cardinal(*file, "EA ", args, 3))
      return (1);
    else if (handle_rgb(*file, "F ", args, 1))
      return (1);
    else if (handle_rgb(*file, "C ", args, 0))
      return (1);
    file++;
  }
  return (0);
}

void init_struct(t_args *args) {
  args->north_texture = NULL;
  args->south_texture = NULL;
  args->west_texture = NULL;
  args->east_texture = NULL;
  args->player_direction = NULL;
  args->player_position = NULL;
  args->floor_color = 0;
  args->ceiling_color = 0;
  args->map = NULL;
}

int create_map_data(char *map, t_args *args) {
  int nbr_lines;
  char **file;
  int flag;

  flag = 0;
  nbr_lines = get_nbr_lines(map);
  if (nbr_lines != 0) {
    file = (char **)malloc(nbr_lines * sizeof(char *));
    file = map_copy(map, file);
    if (handle_struct_data(file, nbr_lines, args) || *file == NULL) {
      printf("There is something wrong on .map file\n");
      flag = 1;
    }
    if (args->floor_color == -1 || args->floor_color == -1) {
      printf("There is something wrong on RGB sintax\n");
      free_on_error(args, 4);
      flag = 1;
    }
    free_file(file, nbr_lines);
    free(file);
  } else
    flag = 1;
  return (flag);
}
