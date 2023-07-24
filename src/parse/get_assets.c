/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_assets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:12:38 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/07/23 21:21:56 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char		*get_path(char **map_data, char *find);
static t_img	get_img(char *file, void *mlx);
static int		get_rgb(char **map_data, char *find);
static int		convert_rgb_to_hex(char **split);

t_map	get_assets(char **map_data, void *mlx)
{
	t_map	map;
	char	*path;

	path = get_path(map_data, "NO ");
	map.assets.north_texture = get_img(path, mlx);
	path = get_path(map_data, "SO ");
	map.assets.south_texture = get_img(path, mlx);
	path = get_path(map_data, "WE ");
	map.assets.west_texture = get_img(path, mlx);
	path = get_path(map_data, "EA ");
	map.assets.east_texture = get_img(path, mlx);
	map.assets.floor_color = get_rgb(map_data, "F ");
	map.assets.ceiling_color = get_rgb(map_data, "C ");
	return (map);
}

static char	*get_path(char **map_data, char *find)
{
	char	*path;
	size_t	i;
	size_t	spaces;

	i = 0;
	while (map_data[i] != NULL)
	{
		spaces = count_spaces(map_data[i]);
		path = trimm_line(map_data[i] + spaces);
		if (!ft_strncmp(path, find, ft_strlen(find)))
		{
			spaces = count_spaces(path + 2);
			return (path + (spaces + 2));
		}
		i++;
	}
	return (NULL);
}

static t_img	get_img(char *file, void *mlx)
{
	t_img	img;
	int		size;

	size = TILE_SIZE;
	img.mlx_img = mlx_xpm_file_to_image(mlx, file, &size, &size);
	img.addr = mlx_get_data_addr(img.mlx_img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	return (img);
}

static int	get_rgb(char **map_data, char *find)
{
	int		rgb;
	size_t	i;
	size_t	spaces;
	char	*str;
	char	**split;

	i = 0;
	while (map_data[i] != NULL)
	{
		spaces = count_spaces(map_data[i]);
		str = trimm_line(map_data[i] + spaces);
		if (!ft_strncmp(str, find, ft_strlen(find)))
		{
			spaces = count_spaces(str + 1);
			split = ft_split(str + (spaces + 1), ',');
			rgb = convert_rgb_to_hex(split);
			free_split(split);
			return (rgb);
		}
		i++;
	}
	return (0);
}

static int	convert_rgb_to_hex(char **split)
{
	int	red;
	int	green;
	int	blue;

	red = ft_atoi(split[0]);
	green = ft_atoi(split[1]);
	blue = ft_atoi(split[2]);
	return (red << 16 | green << 8 | blue << 0);
}
