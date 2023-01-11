/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bderya <bderya@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 08:09:48 by yogun             #+#    #+#             */
/*   Updated: 2023/01/11 13:29:45 by bderya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

/*
	mlx_get_data_addr returns information about the created image, 
	allowing a user to modify it later.
	mlx_get_data_addr returns a char * address that represents the begining of
	the memory area where the image is stored.

	First input specifies the image to use. 
	The three next parameters should be the addresses of three different ->>
	valid integers.
	Second input will be filled with the number of bits needed to -> 
	represent a pixel color (also called the depth of the image).
	Third input is the number of bytes used to store one line of ->
	the image in memory. 
	This information is needed to move from one line to another in the image.
	Fourth input tells you wether the pixel color in the image needs to be stored in
	little endian endian == 0, or big endian endian == 1.
	First two elements of the array is empty because 
*/
void	ft_get_data_addr(t_dB *db)
{
	if (!(db->ea || db->so || db->we || db->no || \
		db->key || db->door || db->key2))
	{
		write(2, "Error! Image file could not found!\n", 35);
		ft_lstfree(db->map);
		free(db->mlx);
		exit(EXIT_FAILURE);
	}
	db->addr[2] = mlx_get_data_addr(db->no, &db->bits_per_pixel[2],
			&db->line_length[2], &db->endian[2]);
	db->addr[3] = mlx_get_data_addr(db->so, &db->bits_per_pixel[3],
			&db->line_length[3], &db->endian[3]);
	db->addr[4] = mlx_get_data_addr(db->we, &db->bits_per_pixel[4],
			&db->line_length[4], &db->endian[4]);
	db->addr[5] = mlx_get_data_addr(db->ea, &db->bits_per_pixel[5],
			&db->line_length[5], &db->endian[5]);
	db->addr[6] = mlx_get_data_addr(db->door, &db->bits_per_pixel[6],
			&db->line_length[6], &db->endian[6]);
	db->addr[7] = mlx_get_data_addr(db->key, &db->bits_per_pixel[7],
			&db->line_length[7], &db->endian[7]);
	db->addr[8] = mlx_get_data_addr(db->key2, &db->bits_per_pixel[8],
			&db->line_length[8], &db->endian[8]);
}

/*
	This function renders the wall, door and key images. 
	mlx_xpm_file_to_image functions will create a new image.
*/
void	file_to_image(t_dB *db)
{
	int		i;
	char	*tmp;

	i = 64;
	tmp = db->no;
	db->no = mlx_xpm_file_to_image(db->mlx, db->no, &i, &i);
	free(tmp);
	tmp = db->so;
	db->so = mlx_xpm_file_to_image(db->mlx, db->so, &i, &i);
	free(tmp);
	tmp = db->we;
	db->we = mlx_xpm_file_to_image(db->mlx, db->we, &i, &i);
	free(tmp);
	tmp = db->ea;
	db->ea = mlx_xpm_file_to_image(db->mlx, db->ea, &i, &i);
	free(tmp);
	db->door = mlx_xpm_file_to_image(db->mlx, "textures/door.xpm", &i, &i);
	db->key = mlx_xpm_file_to_image(db->mlx, "textures/key_right.xpm", &i, &i);
	db->key2 = mlx_xpm_file_to_image(db->mlx, "textures/key_left.xpm", &i, &i);
	ft_get_data_addr(db);
}

/*
	The function checks the correctness of the data received from the player.
	If the data is incorrect, the program will exit with an error.
	Otherwise, the function will return nothing.
	Also, according to the player's position, the function will set the angle.	
*/
void	ft_player_db_control(t_dB *db)
{
	if (db->player == '\0')
		ft_error("Error! Position of player is not found!\n", db);
	if (db->player == 'E')
		db->pa = 0;
	else if (db->player == 'N')
		db->pa = 90;
	else if (db->player == 'W')
		db->pa = 180;
	else if (db->player == 'S')
		db->pa = 270;
}

/*
	The function checks the correctness of the data received from the map.
	If the data is incorrect, the program will exit with an error.
	Otherwise, the function will return nothing.	
*/
void	ft_map_db_control(t_dB *db)
{
	if (db->no == NULL)
		ft_error("Error! Texture for 'NO' is not found!\n", db);
	if (db->ea == NULL)
		ft_error("Error! Texture for 'EA' is not found!\n", db);
	if (db->we == NULL)
		ft_error("Error! Texture for 'WE' is not found!\n", db);
	if (db->so == NULL)
		ft_error("Error! Texture for 'SO' is not found!\n", db);
	if (db->c[0] < 0)
		ft_error("Error! For ceiling RGB is not found!\n", db);
	if (db->f[0] < 0)
		ft_error("Error! For floor RGB is not found!\n", db);
	if (!db->map)
		ft_error("Error! Map is not found!\n", db);
	ft_player_db_control(db);
}

/*
	This function basically render the game window. Besides,
	it also checks whether the data received from the map.
	it calculates the angles of the player's position.

	Hooking into events is one of the most powerful tools that MiniLibX provides. 
	It allows you to register to any of the aforementioned events 
	with the call of a simple hook registration function.

	To achieve this, we call the function mlx_hook.
	2: ON_KEYDOWN -> For key press moment
	17: ON_DESTROY -> For window close moment little red button with cross
	
	To initiate a loop, we call the mlx_loop function with 
	the mlx instance as only parameter

	The mlx_loop_hook is one hook that is triggered when there's no event processed 
*/
void	ft_game_render(t_dB *db)
{
	ft_map_db_control(db);
	db->pdx = cos(ft_degree_to_radian(db->pa));
	db->pdy = -1 * sin(ft_degree_to_radian(db->pa));
	//db->is_key = '1'; Norm error yeri
	if (db->is_key == '1')
	{
		db->sprite = '1';
		db->is_key = '0';
	}
	// if (KEYS == '1') normm error yeri
	// 	db->is_key = '1'; norm error yeri
	db->key_px += 0.5;
	db->key_py += 0.5;
	db->mlx = mlx_init();
	file_to_image(db);
	db->win = mlx_new_window(db->mlx, WIDTH, HEIGHT, "Cube3D");
	mlx_mouse_hide();
	mlx_hook(db->win, 17, 0, ft_exit_game, db);
	mlx_hook(db->win, 2, 0, ft_key_hook, db);
	// I will continue to write after gym, idk but am gonna fix bderya ..
	mlx_loop_hook(db->mlx, ft_game_start, db);
	mlx_loop(db->mlx);
}
