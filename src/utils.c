/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:45:47 by yogun             #+#    #+#             */
/*   Updated: 2023/01/16 15:10:51 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	my_mlx_pixel_put_mini(t_dB *a, int x, int y, int color)
{
	char	*dst;

	dst = a->addr[1] + ((y * a->line_length[0])
			+ x * (a->bits_per_pixel[0] / 8));
	*(unsigned int *)dst = color;
}

/*
	This function is counting and changing the state of the
	sprite in every 20 frames. According to this, later
	we will render different images to animate things. Such as key :)
*/
void	ft_timer(t_dB *db)
{
	db->loop += 1;
	if (db->loop % 20 == 0)
	{
		if (db->sprite_state == '1')
			db->sprite_state = '2';
		else
			db->sprite_state = '1';
	}
	if (db->loop == 401)
		db->loop = 1;
}
