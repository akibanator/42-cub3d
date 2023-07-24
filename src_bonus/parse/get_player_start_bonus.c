/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player_start_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:17:29 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/07/24 02:18:53 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_vector	get_start_dir(char **grid)
{
	t_vector	start_dir;
	size_t		i;
	size_t		j;

	i = 0;
	start_dir.x = 0;
	start_dir.y = 0;
	while (grid[i] != NULL)
	{
		j = 0;
		while (grid[i][j] != '\0')
		{
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

t_vector	get_start_pos(char **grid)
{
	t_vector	start_pos;
	size_t		i;
	size_t		j;

	i = 0;
	while (grid[i] != NULL)
	{
		j = 0;
		while (grid[i][j] != '\0')
		{
			if (grid[i][j] == 'N' || grid[i][j] == 'S' || grid[i][j] == 'W'
				|| grid[i][j] == 'E')
			{
				start_pos.y = i;
				start_pos.x = j;
			}
			j++;
		}
		i++;
	}
	return (start_pos);
}
