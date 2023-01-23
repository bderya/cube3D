/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:00:58 by yogun             #+#    #+#             */
/*   Updated: 2023/01/23 10:26:58 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	ft_start(char *argv)
{
		t_dB	db;
		ft_initdata(&db);
		if (!ft_check_map_format(argv, ".cub"))
			ft_error("Map format is invalid!\n", &db);
		ft_map_process(&db, argv);
		ft_game_render(&db);
}
