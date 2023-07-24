/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:00:52 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/07/23 21:20:42 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map(char *line)
{
	const int	map_sintax[] = {'0', '1', 'N', 'S', 'E', 'W', ' ', '\0'};
	int			i;
	size_t		j;
	int			flag;

	i = 0;
	line = trimm_line(line);
	while (line[i] != '\0')
	{
		flag = 0;
		j = 0;
		while (map_sintax[j] != '\0')
		{
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
