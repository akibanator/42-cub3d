/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:05:01 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/07/24 02:19:41 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	check_valid_rgb(char *line)
{
	char	**rgb;
	char	*trimmed_rgb;
	size_t	i;
	int		flag;

	rgb = ft_split(line, ',');
	i = 0;
	flag = 0;
	while (rgb[i] != NULL)
	{
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

int	check_map(char *file)
{
	int		fd;
	char	*line;
	int		entries;

	fd = open(file, O_RDONLY);
	entries = 0;
	if (fd < 0)
	{
		printf("Valid data not found in file [%s]\n", file);
		return (1);
	}
	line = ft_get_next_line(fd);
	while (line != NULL)
	{
		entries = entries + check_line(line);
		free(line);
		line = ft_get_next_line(fd);
	}
	close(fd);
	if (entries != 6)
		return (1);
	return (0);
}

int	check_valid_ext(char *map, char *ext)
{
	size_t	i;

	i = 0;
	while (map[i] != '\0')
		i++;
	i--;
	while (map[i] != '\0')
	{
		if (map[i] == '.')
		{
			if (ft_strncmp(map + i, ext, ft_strlen(ext) + 1) == 0)
				return (0);
			return (1);
		}
		i--;
	}
	return (1);
}

int	check_args(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Incorrect number of arguments\n");
		return (1);
	}
	if (check_valid_ext(argv[1], ".cub\0"))
	{
		printf("Invalid file extension\n");
		return (1);
	}
	return (0);
}
