/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:20:04 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/07/23 17:45:25 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char *argv[])
{
	t_data *data;

	if (check_args(argc, argv) || check_map(argv[1]))
	{
		printf("Error\n");
		return (1);
	}
	data = data_init();
	data->map = create_data(argv[1], data->mlx);
	if (check_valid_grid(data->map.grid, data->map.size))
	{
		printf("Error\n");
		return (1);
	}
	hooks_setup(data);
	mlx_loop(data->mlx);
	exit_game(data);
	return (0);
}
