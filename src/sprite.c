/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bderya <bderya@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 22:02:10 by yogun             #+#    #+#             */
/*   Updated: 2023/01/25 13:00:37 by bderya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

/*
	In this function we put pixel of sprite image to the the sprite texutre.
	We check if the sprite is 1 or 2. If it is 1, we use the first image.
	Else, we use the second image. By this way we are generating the animation

	0x000FF00FF is the color of the background of the sprite. By this way,
	we are not putting the background color to the sprite texture. (alpha)
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

/*
	In this function step by step, if there is no sprite, we return.
	We calculate the distance in between player and the sprite(key).
	First we check distance of their x and y coordinates but we multiply
	their distance with 64 because the image is 64*64. We save the value
	as sx and sy are the distance of the sprite with player to our database.
	We give to z value 10. It will be used for the height of the sprite. Height
	or distance from the ground.
	
	Then we calculate the cos and sin components of the sprite. Since, spring
	always should be visible to the player perpendicularly, we can use the
	player's angle to calculate the cos and sin components of the sprite.
	We save the values to the cos and sin variables of the sprite structure.

	We calculate the x and y coordinates of the sprite. We multiply the distance
	of the sprite with the cos and sin components of the sprite. We save
	the values to the x and y variables of the sprite structure.

	We save the spr.y of the sprite to the b variable of the database. This is like
	a constant value. We need to do in this way for raycasting. and all
	these calculations after that point will be done according to the 
	raycasting math.

	P.S.: 800 is an artbitrary value. I chose it proportionally according 
	to the screen size.
	For more information: https://lodev.org/cgtutor/raycasting3.html
*/
void	init_sprite(t_dB *db)
{
	t_sprite	spr;

	if (db->sprite == '0')
		return ;
	db->sx = (db->key_px - db->px) * 64;
	db->sy = (db->key_py - db->py) * 64;
	spr.z = 10;
	spr.cos = cos(ft_degree_to_radian(db->pa));
	spr.sin = sin(ft_degree_to_radian(db->pa));
	spr.x = db->sy * spr.cos + db->sx * spr.sin;
	spr.y = db->sx * spr.cos - db->sy * spr.sin;
	db->b = spr.y;
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
	
	We check if the sprite is in the screen. If it is not, we return.
	
	In second if condition we check if the column number is bigger than the
	starting point of the sprite and smaller than the ending point of the sprite and
	if the distance of the sprite is bigger than the distance of the wall and if the
	distance of the sprite is bigger than 0. If all of these conditions are true, we
	enter the while loop. In the while loop we draw the sprite to the screen. We use
	the put_sprite_pixel function to draw the sprite.
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
