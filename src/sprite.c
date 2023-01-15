/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bderya <bderya@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 22:02:10 by yogun             #+#    #+#             */
/*   Updated: 2023/01/11 14:24:32 by bderya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

/*
	In this function we put pixel of sprite image to the the sprite texutre. 
*/
void	put_sprite_pixel(t_dB *db, int x, int y)
{
	char	*dst;
	int		i;
	int		j;

	i = (int)db->t_x;
	j = (int)db->t_y;
	if (db->sprite_state == '1')
		dst = db->addr[7] + ((j * db->line_length[7])
				+ i * (db->bits_per_pixel[7] / 8));
	else
		dst = db->addr[8] + ((j * db->line_length[8])
				+ i * (db->bits_per_pixel[8] / 8));
	if (*(unsigned int *)dst != 0x000FF00FF)
		my_mlx_pixel_put(db, x, y, *(unsigned int *)dst);
}

void	init_sprite(t_dB *db)
{
	t_sprite	spr;

	// If there is no sprite, return
	if (db->sprite == '0')
		return ;
	db->sx = (db->key_px - db->px) * 64;	// pics are 64*64. This is why we multiply with 64. We calculate distance perpendicularly to the player
	db->sy = (db->key_py - db->py) * 64;
	spr.z = 10;
	spr.cos = cos(ft_degree_to_radian(db->pa)); // cos and sin of player angle 
	spr.sin = sin(ft_degree_to_radian(db->pa));
	// Here we calculate real distance to the sprite
	spr.x = db->sy * spr.cos + db->sx * spr.sin;
	spr.y = db->sx * spr.cos - db->sy * spr.sin;
	db->b = spr.y;
	//printf("sprx: %f, spry: %f\n", spr.x,spr.y);
	db->sx = spr.x * 800 / spr.y + (WIDTH / 2);
	db->sy = spr.z * 800 / spr.y + (HEIGHT / 2);
	db->spr_scale = 5 * HEIGHT / db->b;
	if (db->spr_scale < 0)
		db->spr_scale = 0;
	else if (db->spr_scale > WIDTH / 2)
		db->spr_scale = WIDTH / 2;
	db->t_x = 0;
	db->t_x_step = 63.0 / db->spr_scale;
	db->t_y_step = 64.0 / db->spr_scale;
}

/*
	In this fucntion we draw sprite to the screen.
*/
void	sprite_draw(t_dB *db, int i)
{
	double	y;

	if (db->sprite == '0')
		return ;
	if (i >= (db->sx - db->spr_scale / 2) && i < (db->sx + db->spr_scale / 2)
		&& db->b > 0 && db->b < db->dist)
	{
		db->t_y = 62;
		y = 0;
		while (y < db->spr_scale)
		{
			put_sprite_pixel(db, i, db->sy - y);
			db->t_y -= db->t_y_step;
			if (db->t_y < 0)
				db->t_y = 0;
			y++;
		}
		db->t_x += db->t_x_step;
	}
}
