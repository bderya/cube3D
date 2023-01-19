/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 22:02:26 by yogun             #+#    #+#             */
/*   Updated: 2023/01/19 12:21:12 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

/*
	Here in this function we render the objects on the minimap.
	
	We do it by drawing a square around the object position. The size of the square
	is 1/50 of the total map size. We do drawing by mlx_pixel_put() function. To do
	it we invoke my_mlx_pixel_put_mini() function. This function takes 4 arguments.
	The first one is the database, the second one is the x coordinate, the third one
	is the y coordinate and the last one is the color. The color is the same as the
	color of the object.
*/
void	ft_colors_minimap(t_dB *db, int x, int y, int k)
{
	int	j;
	int	i;

	i = 0;
	while (i <= WIDTH / 50)
	{
		j = 0;
		while (j <= HEIGHT / 50)
		{
			if (i == 0 || j == 0)
				my_mlx_pixel_put_mini(db, i + x * WIDTH / 50,
					j + y * HEIGHT / 50, 0x0FF000000);
			else
				my_mlx_pixel_put_mini(db, i + x * WIDTH / 50,
					j + y * HEIGHT / 50, k);
			j++;
		}
		i++;
	}
}

/*
	Here we render the player on the minimap. We do this by drawing a square around
	the player position. The size of the square is 1/250 of the total map size.
	
	We do drawing by mlx_pixel_put() function. To do it we invoke my_mlx_pixel_put_mini()
	function. This function takes 4 arguments. The first one is the database, the
	second one is the x coordinate, the third one is the y coordinate and the last
	one is the color.
*/
void	ft_player_minimap(t_dB *db, double x, double y)
{
	double	j;
	double	i;

	i = 0.5 - WIDTH / 250;
	while (i <= WIDTH / 250)
	{
		j = 0.5 - HEIGHT / 250;
		while (j <= WIDTH / 250)
		{
			my_mlx_pixel_put_mini(db, i + x * WIDTH / 50,
				j + y * HEIGHT / 50, 0xFFFF31);
			j++;
		}
		i++;
	}
}

/*
	In this function we render the player on the minimap.
	
	In first if condition we check if the player is less than 5 blocks away from the
	top or bottom of the map. If so we move the player up or down so that the player
	is always in the middle of the minimap.
	
	In second if condition we check the player distance from the left or right side
	of the map. If so we move the player left or right so that the player is always
	in the middle of the minimap.

	In first else condition we update player position on the minimap so that the player
	is always in the middle of the minimap.
	
	Then we do same things for the y axis.
	
	Finally we invoke the function that renders the player on the minimap.
*/
void	ft_player_init(t_dB *db)
{
	double	x;
	double	y;

	if (db->px < 5)
		x = db->px;
	else if (db->map_width - db->px < 5)
		x = 10 - (db->map_width - db->px);
	else
		x = 4 + (db->px - (int)db->px);
	if (db->py < 5)
		y = db->py;
	else if (db->map_height - db->py < 5)
		y = 10 - (db->map_height - db->py);
	else
		y = 5 + (db->py - (int)db->py);
	ft_player_minimap(db, x, y);
}

/*
	This is the second part of the minimap function. It is called in the first part
	of the function. It renders the map and invoke the function that renders the player.

	In first if condition we render walls on minimap.
	In second if condition we render doors on minimap.
	In else condition we render empty space on minimap.

	Finally with ft_player_init function we render the player on minimap.
*/
void	ft_sub_minimap(t_list *map, t_dB *db, double x)
{
	int		i;
	int		j;
	char	*line;

	j = 0;
	while (map && j < 10)
	{
		line = map->content;
		i = 0;
		while (line[(int)x + i] && i < 10)
		{
			if (line[(int)x + i] == '1')
				ft_colors_minimap(db, i, j, 0x13AED4);
			else if (line[(int)x + i] == 'D')
				ft_colors_minimap(db, i, j, 0xAE8039);
			else
				ft_colors_minimap(db, i, j, 0x00000000);
			i++;
		}
		j++;
		map = map->nxt;
	}
	ft_player_init(db);
}

/*
	In this function we render the minimap.

	We first check if the minimap is already rendered and if so we destroy it.
	Then we create a new image and get the data address of it. We create the image %20
	of the size of the window. This is going to be the size of the minimap.
	
	We then check if the map is bigger than 11x11. If it is we check if the player is
	less than 6 blocks away from the top or bottom of the map. If so we move the map
	up or down so that the player is always in the middle of the minimap.

	Then we invoke the second part of the function andthen we finish the function with
	putting the image to the window.
	
*/
void	ft_minimap_render(t_list *map, t_dB *db)
{
	double	y;
	double	x;

	if (db->minimap)
		mlx_destroy_image(db->mlx, db->minimap);
	db->minimap = mlx_new_image(db->mlx, WIDTH / 5, HEIGHT / 5);
	db->addr[1] = mlx_get_data_addr(db->minimap, &db->bits_per_pixel[0],
			&db->line_length[0], &db->endian[0]);
	y = 0;
	while (db->map_height > 11 && db->py > y + 6 && db->map_height > y + 10)
	{
		map = map->nxt;
		y++;
	}
	if (db->map_width < 11 || db->px <= 4)
		x = 0;
	else if (db->map_width - db->px <= 6)
		x = db->map_width - 10;
	else
		x = db->px - 4;
	ft_sub_minimap(map, db, x);
	mlx_put_image_to_window(db->mlx, db->win, db->minimap, 0, 0);
}
