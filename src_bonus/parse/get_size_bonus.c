/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:08:19 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/07/24 02:19:00 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static double	get_height(char **map_data);
double			get_width(char **map_data);

t_vector	get_size(char **map_data)
{
	t_vector	size;

	size.y = get_height(map_data);
	size.x = get_width(map_data);
	return (size);
}

static double	get_height(char **map_data)
{
	double	height;
	size_t	i;
	char	*str_trim;

	i = 0;
	height = 0;
	while (map_data[i] != NULL)
	{
		str_trim = trimm_line(map_data[i]);
		if (!ft_strncmp(str_trim, "1", 1))
		{
			height++;
		}
		i++;
	}
	return (height);
}

double	get_width(char **map_data)
{
	double	width;
	size_t	i;
	char	*str_trim;

	i = 0;
	width = 0;
	while (map_data[i] != NULL)
	{
		str_trim = trimm_line(map_data[i]);
		if (!ft_strncmp(str_trim, "1", 1))
		{
			if (width < ft_strlen(map_data[i]))
				width = ft_strlen(map_data[i]);
		}
		i++;
	}
	return (width);
}
