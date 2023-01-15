/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 20:24:22 by yogun             #+#    #+#             */
/*   Updated: 2023/01/10 17:49:17 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

/*
	This function frees all the allocated memory and exits the program.
*/
int	ft_exit_game(t_dB *db)
{
	mlx_destroy_window(db->mlx, db->win);
	ft_free(db);
	exit(EXIT_SUCCESS);
}
