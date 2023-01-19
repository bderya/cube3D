/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:45:47 by yogun             #+#    #+#             */
/*   Updated: 2023/01/19 12:24:03 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

/*
	Here we do update the dst pointer to the next pixel in the image.
	We do this by adding the line length to the dst pointer.
*/
void	my_mlx_pixel_put_mini(t_dB *db, int x, int y, int color)
{
	char	*dst;

	dst = db->addr[1] + ((y * db->line_length[0])
			+ x * (db->bits_per_pixel[0] / 8));
	*(unsigned int *)dst = color;
}

/*
	This function is counting and changing the state of the
	sprite in every 20 frames. According to this, later
	we will render different images to animate things. Such as key :)
	After 400, we reset the loop to 1.
*/
void	ft_timer(t_dB *db)
{
	db->loop += 1;
	if (db->loop % 20 == 0)
	{
		if (db->sprite_state == '1')
			db->sprite_state = '2';
		else if (db->sprite_state == '2')
			db->sprite_state = '1';
	}
	if (db->loop == 401)
		db->loop = 1;
}
