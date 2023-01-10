/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 07:55:40 by yogun             #+#    #+#             */
/*   Updated: 2023/01/09 20:01:27 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

/*
	mlx_get_data_addr is a function of the minilibx library.
	It returns the address of the first pixel of the image.
	mlx_get_data_addr takes 4 arguments.
	1. The image.
	2. The number of bits per pixel.
	3. The length of a line in bytes.
	4. The endian.
*/
void	ft_map_render(t_dB *db)
{
	t_ray		ray;
	//If there is an image, destroy it.
	if (db->img)
		mlx_destroy_image(db->mlx, db->img);
	db->img = mlx_new_image(db->mlx, WIDTH, HEIGHT);	//Create a new image.
	//If the image couldn't be created, print an error message and exit the game.
	if (!db->img)
	{
		write(2, "Error\nImage couldn't be created!\n", 32);
		ft_exit_game(db);
	}
	//Get the address of the first pixel of the image.
	db->addr[1] = mlx_get_data_addr(db->img, &db->bits_per_pixel[1],
			&db->line_length[1], &db->endian[1]);
	init_sprite(db);
	ft_ray_cast(db, &ray);
	mlx_put_image_to_window(db->mlx, db->win, db->img, 0, 0);
}

/*
	This function is called in every frame.
	First, it calls ft_timer() to check if the player is moving.
	Then, it calls ft_map_render() to render the map.
	After that, it calls ft_minimap_render() to render the minimap.
	Then, it checks if the mouse is moved to the right or left.
	Finally, it checks if the player is in the door and if the door is open.
	If the player is in the door and the door is open, it calls put_map_char()
	to put a 'D' on the map. This is to make sure that the player can't go
	through the door.	
*/
int	ft_game_start(t_dB *db)
{
	int	x;

	ft_timer(db);
	ft_map_render(db);
	ft_minimap_render(db->map, db);
	x = db->mouse_x;
	mlx_mouse_get_pos(db->win, &db->mouse_x, &db->mouse_y);
	if (db->mouse_x > x)
		right_key(db);
	else if (db->mouse_x < x)
		left_key(db);
	if (db->is_open == '1' && db->step_num > 20
		&& ((int)db->px != db->d_x || (int)db->py != db->d_y))
		put_map_char(db->d_x, db->d_y, db, 'D');
	return (0);
}
