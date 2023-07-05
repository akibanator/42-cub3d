#include "cub3d.h"

int check_valid_ext(char *map, char *ext) {
  while (*map != '\0') {
    if (*map == '.') {
      if (ft_strncmp(map, ext, ft_strlen(ext)) == 0)
        return (0);
    }
    map++;
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
