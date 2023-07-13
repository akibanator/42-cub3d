#include "cub3d.h"
#include <fcntl.h>
#include <stdlib.h>

static int check_valid_file(char *line) {
  int fd;

  fd = open(line, O_RDONLY);
  if (fd < 0) {
    close(fd);
    return (1);
  }
  close(fd);
  return (0);
}

int handle_cardinal(char *line, char *info, t_args *args, int cord) {
  if (*line != '\n') {
    line = skip_spaces(line);
    if (ft_strncmp(line, info, ft_strlen(info)) == 0) {
      line = skip_spaces(line + 2);
      line = ft_substr(line, 0, ft_strlen(line) - 1);
      if (check_valid_ext(line, ".xpm\0") || check_valid_file(line)) {
        printf("Invalid texture file\n");
        free_on_error(args, cord + 1);
        return (1);
      }
      if (cord == 0)
        args->north_texture = line;
      else if (cord == 1)
        args->south_texture = line;
      else if (cord == 2)
        args->west_texture = line;
      else if (cord == 3)
        args->east_texture = line;
    }
  }
  return (0);
}
