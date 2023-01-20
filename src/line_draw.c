/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 22:04:30 by yogun             #+#    #+#             */
/*   Updated: 2023/01/17 17:43:01 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

/*
	In this function we put color pixels to the screen. We use this function
	to draw the floor and ceiling colors.
*/
void	my_mlx_pixel_put(t_dB *db, int x, int y, int color)
{
	char	*dst;

	dst = db->addr[1] + ((y * db->line_length[1]) + x
			* (db->bits_per_pixel[1] / 8));
	*(unsigned int *)dst = color;
}

// RGB conversion to the decimal number
int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/*
	This function put image pixels to the texture areas.
*/
void	put_texture_pixel(t_dB *db, int x, int y, int k)
{
	char	*dst;
	int		i;
	int		j;

	if (db->linelen == 0)
		return ;
	i = db->ray;
	k = k + db->stepy;
	j = (k << 6) / db->linelen;
	dst = db->addr[db->zeros] + ((j * db->line_length[db->zeros])
			+ i * (db->bits_per_pixel[db->zeros] / 8));
	my_mlx_pixel_put(db, x, y, *(unsigned int *)dst);
}

/*
	This function draw the fllor and ceiling colors or put images to the
	other parts of the game.
	In first if condition we draw the ceiling with RGB values.
	In second if condition we draw the floor with RGB values.
	In else condition we put the image pixels to the walls or doors.
*/
void	line_draw_2(t_dB *db, int i, int lineh, int lineoff)
{
	int	k;
	int	y;

	k = -1;
	y = 0;
	while (y < HEIGHT)
	{
		if (y < lineoff)
			my_mlx_pixel_put(db, i, y,
				create_trgb(0, db->c[0], db->c[1], db->c[2]));
		else if (y > lineh + lineoff)
			my_mlx_pixel_put(db, i, y,
				create_trgb(0, db->f[0], db->f[1], db->f[2]));
		else
			put_texture_pixel(db, i, y, k++);
		y++;
	}
}

/*
	lineh = lineheight
	lineoff = line offset to center the screen

	This function draw the walls and put textures to the walls.
	If the lineheight is bigger than the screen height, we cut the line
	to the screen height and put the rest of the line to the floor and
	ceiling.
*/
void	line_draw(t_dB *db, int i)
{
	int	lineh;
	int	lineoff;

	lineh = (HEIGHT << 5) / db->dist;
	db->stepy = 0;
	db->linelen = lineh;
	if (lineh > HEIGHT)
	{
		db->stepy = ((lineh - HEIGHT) >> 1);
		lineh = HEIGHT;
	}
	lineoff = (HEIGHT - lineh) >> 1;
	line_draw_2(db, i, lineh, lineoff);
}
