/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:20:04 by bcorrea-          #+#    #+#             */
/*   Updated: 23/07/2023 02:59:16 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char *argv[])
{
	t_data *data;

	if (check_args(argc, argv))
		return (1);
	if (check_map(argv[1]))
		return (1);
	data = data_init();
	data->map = create_data(argv[1], data->mlx);
	hooks_setup(data);
	mlx_loop(data->mlx);
	exit_game(data);
	return (0);
}
