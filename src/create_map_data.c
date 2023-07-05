#include "cub3d.h"
#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>

static int get_nbr_lines(char *map) {
  int fd;
  char *line;
  int nbr_lines;
  nbr_lines = 0;
  fd = open(map, O_RDONLY);
  if (fd < 0) {
    printf("Map data not found in file [%s]\n", map);
    exit(0);
  }
  line = ft_get_next_line(fd);
  while (line != NULL) {
    nbr_lines++;
    free(line);
    line = ft_get_next_line(fd);
  }
  close(fd);
  return (nbr_lines);
}

static char **map_copy(char *map, char **file) {
  int fd;
  char *line;
  char **head_file;
  fd = open(map, O_RDONLY);
  head_file = file;
  if (fd < 0) {
    printf("Map data not found in file [%s]\n", map);
    exit(0);
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

static void free_file(char **file, int nbr_lines) {
  while (nbr_lines--) {
    free(*file);
    file++;
  }
}

static char *skip_spaces(char *line) {
  while (*line != '\0' && *line == ' ' && *line != '\n')
    line++;
  return (line);
}

static void free_on_error(t_args *args, int num) {
  if (num > 0)
    free(args->north_texture);
  if (num > 1)
    free(args->south_texture);
  if (num > 2)
    free(args->west_texture);
  if (num > 3)
    free(args->east_texture);
}

static int handle_cardinal(char *line, char *info, t_args *args, int cord) {
  if (*line != '\n') {
    line = skip_spaces(line);
    if (ft_strncmp(line, info, ft_strlen(info)) == 0) {
      if (check_valid_ext(line, ".xpm\n")) {
        printf("Invalid texture file extension\n");
        free_on_error(args, cord);
        return (1);
      }
      line = skip_spaces(line + 2);
      if (cord == 0)
        args->north_texture = ft_substr(line, 0, ft_strlen(line) - 1);
      else if (cord == 1)
        args->south_texture = ft_substr(line, 0, ft_strlen(line) - 1);
      else if (cord == 2)
        args->west_texture = ft_substr(line, 0, ft_strlen(line) - 1);
      else if (cord == 3)
        args->east_texture = ft_substr(line, 0, ft_strlen(line) - 1);
    }
  }
  return (0);
}

// TODO: handle rgb
// TODO: handle map

static int handle_struct_data(char **file, int nbr_lines, t_args *args) {
  while (nbr_lines--) {
    if (handle_cardinal(*file, "NO ", args, 0))
      return (1);
    if (handle_cardinal(*file, "SO ", args, 1))
      return (1);
    if (handle_cardinal(*file, "WE ", args, 2))
      return (1);
    if (handle_cardinal(*file, "EA ", args, 3))
      return (1);
    file++;
  }
  return (0);
}

int create_map_data(char *map, t_args *args) {
  int nbr_lines;
  char **file;
  int flag;

  flag = 0;
  nbr_lines = get_nbr_lines(map);
  file = (char **)malloc(nbr_lines * sizeof(char *));
  file = map_copy(map, file);
  if (handle_struct_data(file, nbr_lines, args)) {
    printf("There is something wrong on .map file\n");
    flag = 1;
  }
  free_file(file, nbr_lines);
  free(file);
  return (flag);
}
