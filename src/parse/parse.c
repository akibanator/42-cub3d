#include "cub3d.h"
#include <fcntl.h>

size_t count_spaces(char *line) {
  size_t i;

  i = 0;
  while (line[i] != '\0' && line[i] == ' ')
    i++;
  return (i);
}

char *trimm_line(char *line) {
  size_t i;
  size_t len;

  i = count_spaces(line);
  len = ft_strlen(line);
  if (len == 0)
    return (line);
  len--;
  while (line[len] != '\0' && len != 0) {
    if (line[len] == ' ' || line[len] == '\n')
      line[len] = '\0';
    else
      break;
    len--;
  }
  return (line + i);
}

int is_cardinal(char *line) {
  int fd;

  line = trimm_line(line);
  if (check_valid_ext(line, ".xpm"))
    return (1);
  fd = open(line, O_RDONLY);
  if (fd < 0)
    return (1);
  close(fd);
  return (0);
}

int check_valid_rgb(char *line) {
  char **rgb;
  char *trimmed_rgb;
  size_t i;
  int flag;

  rgb = ft_split(line, ',');
  i = 0;
  flag = 0;
  while (rgb[i] != NULL) {
    trimmed_rgb = trimm_line(rgb[i]);
    if (ft_strlen(trimmed_rgb) == 3)
      if (trimmed_rgb[0] < '0' || trimmed_rgb[0] > '2')
        flag = 1;
    i++;
  }
  if (i != 3)
    flag = 1;
  free_split(rgb);
  return (flag);
}

int is_rgb(char *line) {
  size_t i;
  size_t comma;
  int valid_rgb;

  comma = 0;
  i = 0;
  valid_rgb = 0;
  line = trimm_line(line);
  while (line[i] != '\0') {
    if (line[i] != ' ') {
      valid_rgb++;
      if (line[i] == ',') {
        comma++;
        valid_rgb = 0;
      } else if (!ft_isdigit(line[i]))
        return (1);
    }
    if (valid_rgb > 3)
      return (1);
    i++;
  }
  if (comma != 2)
    return (1);
  if (check_valid_rgb(line))
    return (1);
  return (0);
}

int is_map(char *line) {
  const int map_sintax[] = {'0', '1', 'N', 'S', 'E', 'W', ' ', '\0'};
  int i;
  size_t j;
  int flag;

  i = 0;
  line = trimm_line(line);
  while (line[i] != '\0') {
    flag = 0;
    j = 0;
    while (map_sintax[j] != '\0') {
      if (map_sintax[j] == line[i])
        flag = 1;
      j++;
    }
    if (!flag)
      return (1);
    i++;
  }
  return (0);
}

int is_cardinal_line(char *line) {
  const char *cardinal[] = {"NO ", "SO ", "WE ", "EA ", NULL};
  size_t i;

  i = 0;
  while (cardinal[i] != NULL) {
    if (!ft_strncmp(line, cardinal[i], ft_strlen(cardinal[i])))
      if (!is_cardinal(line + 3))
        return (1);
    i++;
  }
  return (0);
}

int is_rgb_line(char *line) {
  const char *rgb[] = {"F ", "C ", NULL};
  size_t i;

  i = 0;
  while (rgb[i] != NULL) {
    if (!ft_strncmp(line, rgb[i], ft_strlen(rgb[i])))
      if (!is_rgb(line + 2))
        return (1);
    i++;
  }
  return (0);
}

int is_entry(char *line) {
  if (is_cardinal_line(line))
    return (1);
  if (is_rgb_line(line))
    return (1);
  if (!ft_strncmp(line, "1", 1) || !ft_strncmp(line, " ", 1))
    if (is_map(line))
      return (1);
  return (0);
}

int check_line(char *line) {
  size_t i;

  i = count_spaces(line);
  if (line[i] == '\0')
    return (0);
  if (is_entry(line + i))
    return (1);
  return (0);
}

int check_map(char *file) {
  int fd;
  char *line;
  int entries;

  fd = open(file, O_RDONLY);
  entries = 0;
  if (fd < 0) {
    printf("Valid data not found in file [%s]\n", file);
    return (1);
  }
  line = ft_get_next_line(fd);
  while (line != NULL) {
    entries = entries + check_line(line);
    free(line);
    line = ft_get_next_line(fd);
  }
  close(fd);
  if (entries != 6)
    return (1);
  return (0);
}

int check_valid_ext(char *map, char *ext) {
  size_t i;

  i = 0;
  while (map[i] != '\0')
    i++;
  i--;
  while (map[i] != '\0') {
    if (map[i] == '.') {
      if (ft_strncmp(map + i, ext, ft_strlen(ext) + 1) == 0)
        return (0);
      return (1);
    }
    i--;
  }
  return (1);
}

int check_args(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Incorrect number of arguments\n");
    return (1);
  }
  if (check_valid_ext(argv[1], ".cub\0")) {
    printf("Invalid file extension\n");
    return (1);
  }
  return (0);
}
