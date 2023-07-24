/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_entry_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:51:31 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/07/24 02:19:18 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_entry(char *line)
{
	if (is_cardinal_line(line))
		return (1);
	if (is_rgb_line(line))
		return (1);
	if (!ft_strncmp(line, "1", 1) || !ft_strncmp(line, " ", 1))
		if (is_map(line))
			return (1);
	return (0);
}

int	check_line(char *line)
{
	size_t	i;

	i = count_spaces(line);
	if (line[i] == '\0')
		return (0);
	if (is_entry(line + i))
		return (1);
	return (0);
}
