/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimm_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:04:00 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/07/23 21:04:08 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	count_spaces(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0' && line[i] == ' ')
		i++;
	return (i);
}

char	*trimm_line(char *line)
{
	size_t	i;
	size_t	len;

	i = count_spaces(line);
	len = ft_strlen(line);
	if (len == 0)
		return (line);
	len--;
	while (line[len] != '\0' && len != 0)
	{
		if (line[len] == ' ' || line[len] == '\n')
			line[len] = '\0';
		else
			break ;
		len--;
	}
	return (line + i);
}
