/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_grid_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:45:13 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/07/24 02:19:06 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	is_grid_border(char **grid, int height, int width)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (grid[i] != NULL)
	{
		j = 0;
		while (grid[i][j] != '\0')
		{
			if (grid[0][j] != '1')
				return (1);
			if (grid[i][0] != '1')
				return (1);
			if (grid[height - 1][j] != '1')
				return (1);
			if (grid[i][width - 1] != '1')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	is_valid_player(char **grid)
{
	size_t	i;
	size_t	j;
	size_t	p_count;

	i = 0;
	p_count = 0;
	while (grid[i] != NULL)
	{
		j = 0;
		while (grid[i][j] != '\0')
		{
			if (grid[i][j] == 'N' || grid[i][j] == 'S' || grid[i][j] == 'W'
				|| grid[i][j] == 'E')
				p_count++;
			j++;
		}
		i++;
	}
	if (p_count != 1)
		return (1);
	return (0);
}

int	check_valid_grid(char **grid, t_vector size)
{
	int	height;
	int	width;

	height = (int)size.y;
	width = (int)size.x;
	if (is_grid_border(grid, height, width))
		return (1);
	if (is_valid_player(grid))
		return (1);
	return (0);
}
