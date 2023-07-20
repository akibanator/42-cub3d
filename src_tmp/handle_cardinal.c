#include "cub3d.h"
#include <fcntl.h>
#include <stdlib.h>

static int check_valid_file(char *line) {
  int fd;

  fd = open(line, O_RDONLY);
  if (fd < 0) {
    return (1);
  }
  close(fd);
  return (0);
}

static int check_cardinal_args(t_args *args, char *line, int cord) {
  if (cord == 0 && args->north_texture == NULL) {
    args->north_texture = line;
  } else if (cord == 1 && args->south_texture == NULL) {
    args->south_texture = line;
  } else if (cord == 2 && args->west_texture == NULL) {
    args->west_texture = line;
  } else if (cord == 3 && args->east_texture == NULL) {
    args->east_texture = line;
  } else
    return (1);
  return (0);
}

int handle_cardinal(char *line, char *info, t_args *args, int cord) {
  char *new_line;

  if (*line != '\n') {
    line = skip_spaces(line);
    if (ft_strncmp(line, info, ft_strlen(info)) == 0) {
      line = skip_spaces(line + 2);
      new_line = ft_substr(line, 0, ft_strlen(line) - 1);
      if (check_valid_ext(new_line, ".xpm\0") || check_valid_file(new_line)) {
        printf("Invalid texture file\n");
        free(new_line);
        free_on_error(args, cord);
        return (1);
      }
      if (check_cardinal_args(args, new_line, cord)) {
        printf("Repeated cardinal entries was found\n");
        free(new_line);
        free_on_error(args, cord + 1);
        return (1);
      }
    }
  }
  return (0);
}
