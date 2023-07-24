/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:45:11 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/07/20 19:45:11 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_ray_inside_map(t_ray ray, t_map map)
{
	if (ray.hit.x < 0 && ray.hit.x > map.size.x * TILE_SIZE)
		return (FALSE);
	else if (ray.hit.y < 0 && ray.hit.y > map.size.y * TILE_SIZE)
		return (FALSE);
	return (TRUE);
}
