/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_rgb_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:59:03 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/07/23 22:00:24 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_rgb(char *line);
static int	get_comma_count(char *line);

int	is_rgb_line(char *line)
{
	const char	*rgb[] = {"F ", "C ", NULL};
	size_t		i;

	i = 0;
	while (rgb[i] != NULL)
	{
		if (!ft_strncmp(line, rgb[i], ft_strlen(rgb[i])))
			if (!is_rgb(line + 2))
				return (1);
		i++;
	}
	return (0);
}

static int	is_rgb(char *line)
{
	size_t	comma;

	line = trimm_line(line);
	comma = get_comma_count(line);
	if (comma != 2)
		return (1);
	if (check_valid_rgb(line))
		return (1);
	return (0);
}

static int	get_comma_count(char *line)
{
	int	comma;
	int	valid_rgb;
	int	i;

	i = 0;
	valid_rgb = 0;
	comma = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ')
		{
			valid_rgb++;
			if (line[i] == ',')
			{
				comma++;
				valid_rgb = 0;
			}
			else if (!ft_isdigit(line[i]))
				return (1);
		}
		if (valid_rgb > 3)
			return (1);
		i++;
	}
	return (comma);
}
