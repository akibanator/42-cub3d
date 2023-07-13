#include "cub3d.h"
#include <fcntl.h>

int check_valid_ext(char *map, char *ext) {
  while (*map != '\0')
    map++;
  map--;
  while (*map != '\0') {
    if (*map == '.') {
      printf("map: [%s] | ext: [%s] | extlen: [%ld] | strncmp: [%d]\n", map,
             ext, ft_strlen(ext), ft_strncmp(map, ext, ft_strlen(ext)));
      if (ft_strncmp(map, ext, ft_strlen(ext) + 1) == 0)
        return (0);
      return (1);
    }
    map--;
  }
  return (1);
}

void check_args(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Incorrect number of arguments\n");
    exit(0);
  }
  if (check_valid_ext(argv[1], ".cub\0")) {
    printf("Invalid file extension\n");
    exit(0);
  }
}

int get_nbr_lines(char *map) {
  int fd;
  char *line;
  int nbr_lines;
  nbr_lines = 0;
  fd = open(map, O_RDONLY);
  if (fd < 0) {
    printf("Map data not found in file [%s]\n", map);
    return (0);
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

char *skip_spaces(char *line) {
  while (*line != '\0' && *line == ' ' && *line != '\n')
    line++;
  return (line);
}
