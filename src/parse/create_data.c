#include "cub3d.h"
#include "mlx.h"
#include <fcntl.h>

double get_height(char **map_data) {
  double height;
  size_t i;
  char *str_trim;

  i = 0;
  height = 0;
  while (map_data[i] != NULL) {
    str_trim = trimm_line(map_data[i]);
    if (!ft_strncmp(str_trim, "1", 1)) {
      height++;
    }
    i++;
  }
  return (height);
}

double get_width(char **map_data) {
  double width;
  size_t i;
  char *str_trim;

  i = 0;
  width = 0;
  while (map_data[i] != NULL) {
    str_trim = trimm_line(map_data[i]);
    if (!ft_strncmp(str_trim, "1", 1)) {
      if (width < ft_strlen(map_data[i]))
        width = ft_strlen(map_data[i]);
    }
    i++;
  }
  return (width);
}

t_vector get_size(char **map_data) {
  t_vector size;

  size.y = get_height(map_data);
  size.x = get_width(map_data);
  return (size);
}

t_img get_img(char *file, void *mlx) {
  t_img img;
  int size;

  size = TILE_SIZE;
  img.mlx_img = mlx_xpm_file_to_image(mlx, file, &size, &size);
  img.addr = mlx_get_data_addr(img.mlx_img, &img.bits_per_pixel,
                               &img.line_length, &img.endian);
  return (img);
}

size_t get_nbr_lines(char *file) {
  size_t i;
  char *line;
  int fd;

  i = 0;
  fd = open(file, O_RDONLY);
  if (fd < 0) {
    printf("Map data not found in file [%s]\n", file);
    return (0);
  }
  line = ft_get_next_line(fd);
  while (line != NULL) {
    i++;
    free(line);
    line = ft_get_next_line(fd);
  }
  close(fd);
  return (i);
}

char **get_map_data(char *file) {
  char **map_data;
  char *line;
  int fd;
  size_t i;

  map_data = malloc((get_nbr_lines(file) + 1) * sizeof(char *));
  i = 0;
  if (map_data == NULL)
    return (NULL);
  fd = open(file, O_RDONLY);
  if (fd < 0) {
    printf("Map data not found in file [%s]\n", file);
    return (NULL);
  }
  line = ft_get_next_line(fd);
  while (i < get_nbr_lines(file)) {
    map_data[i] = ft_substr(line, 0, ft_strlen(line) - 1);
    free(line);
    line = ft_get_next_line(fd);
    i++;
  }
  map_data[i] = NULL;
  close(fd);
  return (map_data);
}

char *get_path(char **map_data, char *find) {
  char *path;
  size_t i;
  size_t spaces;

  i = 0;
  while (map_data[i] != NULL) {
    spaces = count_spaces(map_data[i]);
    path = trimm_line(map_data[i] + spaces);
    if (!ft_strncmp(path, find, ft_strlen(find))) {
      spaces = count_spaces(path + 2);
      return (path + (spaces + 2));
    }
    i++;
  }
  return (NULL);
}

int convert_rgb_to_hex(char **split) {
  int red;
  int green;
  int blue;

  red = ft_atoi(split[0]);
  green = ft_atoi(split[1]);
  blue = ft_atoi(split[2]);
  return (red << 16 | green << 8 | blue << 0);
}

void free_split(char **split) {
  int i;

  i = 0;
  while (split[i]) {
    free(split[i]);
    i++;
  }
  free(split);
}

int get_rgb(char **map_data, char *find) {
  int rgb;
  size_t i;
  size_t spaces;
  char *str;
  char **split;

  i = 0;
  while (map_data[i] != NULL) {
    spaces = count_spaces(map_data[i]);
    str = trimm_line(map_data[i] + spaces);
    if (!ft_strncmp(str, find, ft_strlen(find))) {
      spaces = count_spaces(str + 1);
      split = ft_split(str + (spaces + 1), ',');
      rgb = convert_rgb_to_hex(split);
      free_split(split);
      return (rgb);
    }
    i++;
  }
  return (0);
}

t_map get_assets(char **map_data, void *mlx) {
  t_map map;
  char *path;

  path = get_path(map_data, "NO ");
  // map.assets.north_texture = get_img(path, mlx);
  path = get_path(map_data, "SO ");
  // map.assets.south_texture = get_img(path, mlx);
  path = get_path(map_data, "WE ");
  // map.assets.west_texture = get_img(path, mlx);
  path = get_path(map_data, "EA ");
  // map.assets.east_texture = get_img(path, mlx);
  (void)path;
  (void)mlx;
  map.assets.floor_color = get_rgb(map_data, "F ");
  map.assets.ceiling_color = get_rgb(map_data, "C ");
  return (map);
}

char **mapcpy(char **map_data, char **grid, int width) {
  int i;
  int k;
  int j;
  size_t spaces;

  i = 0;
  k = 0;
  while (map_data[i] != NULL) {
    spaces = count_spaces(map_data[i]);
    j = 0;
    if (!ft_strncmp(map_data[i] + spaces, "1", 1)) {
      while (j < width && map_data[i][j] != '\0') {
        if (map_data[i][j] == ' ')
          grid[k][j] = '1';
        else
          grid[k][j] = map_data[i][j];
        j++;
      }
      while (j < width) {
        grid[k][j] = '1';
        j++;
      }
      k++;
    }
    i++;
  }
  return (grid);
}

char **get_grid(char **map_data, t_vector size) {
  char **grid;
  int i;
  int height;
  int width;

  i = 0;
  height = (int)size.y;
  width = (int)size.x;
  grid = malloc((height + 1) * sizeof(char *));
  while (i < height) {
    grid[i] = malloc((width + 1) * sizeof(char));
    grid[i][width] = '\0';
    i++;
  }
  grid[i] = NULL;
  grid = mapcpy(map_data, grid, width);
  return (grid);
}

t_vector get_start_dir(char **grid) {
  t_vector start_dir;
  size_t i;
  size_t j;

  i = 0;
  start_dir.x = 0;
  start_dir.y = 0;
  while (grid[i] != NULL) {
    j = 0;
    while (grid[i][j] != '\0') {
      if (grid[i][j] == 'N')
        start_dir.y = 1;
      if (grid[i][j] == 'S')
        start_dir.y = -1;
      if (grid[i][j] == 'W')
        start_dir.x = -1;
      if (grid[i][j] == 'E')
        start_dir.x = 1;
      j++;
    }
    i++;
  }
  return (start_dir);
}

t_vector get_start_pos(char **grid) {
  t_vector start_pos;
  size_t i;
  size_t j;

  i = 0;
  while (grid[i] != NULL) {
    j = 0;
    while (grid[i][j] != '\0') {
      if (grid[i][j] == 'N' || grid[i][j] == 'S' || grid[i][j] == 'W' ||
          grid[i][j] == 'E') {
        start_pos.y = i;
        start_pos.x = j;
      }
      j++;
    }
    i++;
  }
  return (start_pos);
}

t_map create_data(char *file, void *mlx) {
  t_map map;
  char **map_data;

  map_data = get_map_data(file);
  map = get_assets(map_data, mlx);
  map.size = get_size(map_data);
  map.grid = get_grid(map_data, map.size);
  map.start_dir = get_start_dir(map.grid);
  map.start_pos = get_start_pos(map.grid);

  free_split(map_data);
  return (map);
}
