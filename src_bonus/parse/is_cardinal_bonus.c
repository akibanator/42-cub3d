/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cardinal_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:57:21 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/07/24 02:19:12 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	is_cardinal(char *line);

int	is_cardinal_line(char *line)
{
	const char	*cardinal[] = {"NO ", "SO ", "WE ", "EA ", NULL};
	size_t		i;

	i = 0;
	while (cardinal[i] != NULL)
	{
		if (!ft_strncmp(line, cardinal[i], ft_strlen(cardinal[i])))
			if (!is_cardinal(line + 3))
				return (1);
		i++;
	}
	return (0);
}

static int	is_cardinal(char *line)
{
	int	fd;

	line = trimm_line(line);
	if (check_valid_ext(line, ".xpm"))
		return (1);
	fd = open(line, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	return (0);
}
