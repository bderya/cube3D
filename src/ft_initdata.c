/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initdata.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bderya <bderya@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:02:05 by yogun             #+#    #+#             */
/*   Updated: 2023/01/11 13:36:18 by bderya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

/*
	This function initializes all the variables in the struct.
*/
void	ft_initdata_sub2(t_dB *db)
{
	db->map_height = 0;
	db->map_width = 0;
	db->player = '\0';
	db->c[0] = -1;
	db->f[0] = -1;
	db->mouse = '\0';
	db->is_key = '0';
	db->sprite = '0';
	db->sprite_state = '1';
	db->key_py = 1;
	db->key_px = 0;
	db->d_x = -1;
	db->d_y = -1;
	db->angle = 60.0 / WIDTH;
}

/*
	This function initializes all the variables in the struct.
*/
void	ft_initdata(t_dB *db)
{
	int	array_counter;

	array_counter = -1;
	db->ea = NULL;
	db->no = NULL;
	db->so = NULL;
	db->we = NULL;
	db->img = NULL;
	db->line = NULL;
	db->map = NULL;
	db->win = NULL;
	db->door = NULL;
	db->minimap = NULL;
	db->key = NULL;
	db->key2 = NULL;
	db->mlx = NULL;
	while (array_counter < 9)
	{
		array_counter++;
		db->addr[array_counter] = NULL;
	}
	ft_initdata_sub2(db);
}
