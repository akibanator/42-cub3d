/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:15:13 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/07/23 23:24:18 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**mapcpy(char **map_data, char **grid, int width);
static void	set_grid_line(char **map_data, char *grid, int line, int width);

char	**get_grid(char **map_data, t_vector size)
{
	char	**grid;
	int		i;
	int		height;
	int		width;

	i = 0;
	height = (int)size.y;
	width = (int)size.x;
	grid = malloc((height + 1) * sizeof(char *));
	while (i < height)
	{
		grid[i] = malloc((width + 1) * sizeof(char));
		grid[i][width] = '\0';
		i++;
	}
	grid[i] = NULL;
	grid = mapcpy(map_data, grid, width);
	return (grid);
}

static char	**mapcpy(char **map_data, char **grid, int width)
{
	int		line;
	int		row;
	size_t	start_index;

	line = 0;
	row = 0;
	while (map_data[line] != NULL)
	{
		start_index = count_spaces(map_data[line]);
		if (!ft_strncmp(map_data[line] + start_index, "1", 1))
		{
			set_grid_line(map_data, grid[row], line, width);
			row++;
		}
		line++;
	}
	return (grid);
}

static void	set_grid_line(char **map_data, char *grid, int line, int width)
{
	int	col;

	col = 0;
	while (col < width && map_data[line][col] != '\0')
	{
		if (map_data[line][col] == ' ')
			grid[col] = '1';
		else
			grid[col] = map_data[line][col];
		col++;
	}
	while (col < width)
	{
		grid[col] = '1';
		col++;
	}
}
