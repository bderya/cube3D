/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:50:16 by yogun             #+#    #+#             */
/*   Updated: 2023/01/12 14:50:18 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*
	This function works only if we have 2 arguments. It checks if the format of
	the map is correct. If it is, it calls ft_map_process to process the map.
	Then it calls game_start to start the game.

	If we have more than 2 arguments, it prints an error message.
*/
int	main(int argc, char **argv)
{
	t_dB	db;

	if (argc == 2)
	{
		ft_initdata(&db);
		if (!ft_check_map_format(argv[1], ".cub"))
			ft_error("Map format is invalid!\n", &db);
		ft_map_process(&db, argv[1]);
		//after gym norm error yeri.
		ft_game_render(&db);
		//system("leaks cub3D"); norm error yeri .
	}
	else
		ft_putstr_fd("Error!\nProgram accept only one argument!\n", 2);
	return (1);
}
