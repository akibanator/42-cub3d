/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:10:13 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/07/23 21:31:53 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static size_t	get_nbr_lines(char *file);
static char		**get_lines(int fd, char *filename);

char	**get_map_data(char *file)
{
	char	**map_data;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("Map data not found in file [%s]\n", file);
		return (NULL);
	}
	map_data = get_lines(fd, file);
	return (map_data);
}

static char	**get_lines(int fd, char *filename)
{
	char	**lines;
	char	*line;
	size_t	i;

	lines = malloc((get_nbr_lines(filename) + 1) * sizeof(char *));
	if (lines == NULL)
		return (NULL);
	line = ft_get_next_line(fd);
	i = 0;
	while (i < get_nbr_lines(filename))
	{
		lines[i] = ft_substr(line, 0, ft_strlen(line) - 1);
		free(line);
		line = ft_get_next_line(fd);
		i++;
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}

static size_t	get_nbr_lines(char *file)
{
	size_t	i;
	char	*line;
	int		fd;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("Map data not found in file [%s]\n", file);
		return (0);
	}
	line = ft_get_next_line(fd);
	while (line != NULL)
	{
		i++;
		free(line);
		line = ft_get_next_line(fd);
	}
	close(fd);
	return (i);
}
