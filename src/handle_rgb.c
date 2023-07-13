#include "cub3d.h"

static int check_commas(char *line) {
  int nb_comma;

  nb_comma = 0;
  while (*line != '\0') {
    if (*line == ',')
      nb_comma++;
    line++;
  }
  return (nb_comma);
}

static int handle_limits_digit(char *line) {
  int count;
  char *head;

  count = 0;
  head = line;
  while (*head != '\0')
    head++;
  while (count < 3) {
    head--;
    count++;
    if (count > 3 || !ft_isdigit(*head))
      return (-1);
    if (count == 1 && (*head < '0' || *head > '5'))
      return (-1);
    else if (count == 2 && (*head < '0' || *head > '5'))
      return (-1);
    else if (count == 3 && (*head < '0' || *head > '2'))
      return (-1);
  }
  return (ft_atoi(line));
}

static int check_sintax_rgb(char **split_line) {
  int red;
  int green;
  int blue;

  red = handle_limits_digit(*split_line++);
  green = handle_limits_digit(*split_line++);
  blue = handle_limits_digit(*split_line);
  if (red == -1 || green == -1 || blue == -1)
    return (-1);
  return (red << 16 | green << 8 | blue << 0);
}

int handle_rgb(char *line, char *info, t_args *args, int floor) {
  char **split_line;

  if (*line != '\n') {
    line = skip_spaces(line);
    if (ft_strncmp(line, info, ft_strlen(info)) == 0) {
      line = skip_spaces(line + 2);
      line = ft_substr(line, 0, ft_strlen(line) - 1);
      if (check_commas(line) == 2) {
        split_line = ft_split(line, ',');
        if (floor == 1)
          args->floor_color = check_sintax_rgb(split_line);
        else if (floor == 0)
          args->ceiling_color = check_sintax_rgb(split_line);
        free_split(split_line);
      } else {
        printf("There is something wrong in RGB sintax.\n");
        free(line);
        return (1);
      }
      free(line);
    }
  }
  return (0);
}
