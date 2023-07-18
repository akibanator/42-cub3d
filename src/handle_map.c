#include "cub3d.h"
#include "libft.h"

static int get_map_size(t_args *args, char **file, int nbr_lines) {
  size_t tmp_map_width;

  while (nbr_lines--) {
    if (**file == '1' || **file == ' ') {
      tmp_map_width = ft_strlen(*file);
      if (args->map_width < tmp_map_width)
        args->map_width = tmp_map_width;
      args->map_height++;
    }
    file++;
  }
  if (args->map_width < 3 || args->map_height < 3)
    return (1);
  return (0);
}

static char **map_malloc(t_args *args) {
  size_t i;
  size_t j;
  char **omap;

  i = 0;
  omap = malloc(args->map_height * sizeof(char *));
  while (i < args->map_height) {
    omap[i] = malloc((args->map_width + 1) * sizeof(char));
    j = 0;
    while (j < args->map_width) {
      omap[i][j] = '1';
      j++;
    }
    omap[i][j] = '\0';
    i++;
  }
  return (omap);
}

static void strlcpy_map(char *dest, const char *src) {
  size_t i;

  i = 0;
  while ((src[i] != '\0') && (src[i] != '\n')) {
    dest[i] = src[i];
    i++;
  }
  i--;
  while (i < ft_strlen(dest) - 1) {
    dest[i] = '1';
    i++;
  }
  dest[i] = '\0';
}

static void map_copy(char **omap, char **file, int nbr_lines) {
  int i;
  int j;

  i = 0;
  j = 0;
  while (nbr_lines--) {
    if (file[i][0] == '1' || file[i][0] == ' ') {
      strlcpy_map(omap[j], file[i]);
      j++;
    }
    i++;
  }
}

int handle_map(t_args *args, char **file, int nbr_lines) {
  if (get_map_size(args, file, nbr_lines)) {
    printf("Error on map\n");
    free_on_error(args, 4);
    return (1);
  }
  args->map = map_malloc(args);
  if (args->map == NULL) {
    printf("Map malloc error\n");
    free_on_error(args, 4);
    return (1);
  }
  map_copy(args->map, file, nbr_lines);
  // TODO: check map layout
  return (0);
}
