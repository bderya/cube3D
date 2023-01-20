/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 08:09:48 by yogun             #+#    #+#             */
/*   Updated: 2023/01/20 09:01:53 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

/*
	mlx_get_data_addr returns information about the created image, 
	allowing a user to modify it later.

	char *mlx_get_data_addr
	( void *img_ptr, int *bits_per_pixel, int *size_line, int *endian );
	
	mlx_get_data_addr returns a char * address that represents the begining of
	the memory area where the image is stored. From this adress, the first 
	bits_per_pixel bits represent the color of the first pixel in the first
	line of the image. The second group of bits_per_pixel bits represent the
	second pixel of the first line, and so on.

	img_ptr specifies the image which is going to be used. 
	
	*bits_per_pixel will be filled with the number of bits needed to 
	represent a pixel color (also called the depth of the image).
	
	*size_line is the number of bytes used to store one line of
	the image in memory. This information is needed to move from 
	one line to another in the image.
	
	endian tells you wether the pixel color in the image needs 
	to be stored in:
			little endian endian == 0, or big endian endian == 1.
	Little endian reading from right to left, vice versa.
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
	
	void *mlx_xpm_file_to_image
	( void *mlx_ptr, char *filename, int *width, int *height );
	
	mlx_xpm_file_to_image() will return NULL if an error occurs. 
	Otherwise they return a non-null pointer as an image identifier.
	This function will fill it using the specified filename.	
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
	This function checks whether the data in database for player has been initialized.
	
	If the data is initiliaziled, the function will check the player's position.
	According to the letter which has been read from the map(E,N,W,S)
	the function will set the angle of the player.

	This angle is going to determine the beginning direction of the player.	
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
	The function checks the the whether the texture and color data is available
	in the database. If the data is not available, the program will exit with an error.
	
	At the end of the function, the ft_player_db_control will be invoked. In this function,
	the player's position will be checked and the angle will be set.
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
	The ft_map_db_control function checks whether the data in the database is available.
	If the data is not available, the program will exit with an error. Also, in addition
	the player position is checked and set in the function.

	If key is available, the function will check whether the key is collected or not.
	If the key value is 1, the sprite will be activated and key value will be set to 0. 
	It will be set to 1 when the plaayer collect the key.

	Then we call mlx_init function to create a new mlx instance. It returns a pointer to
	the new instance. This pointer will be used in all the other mlx functions.

	We call file_to_image function which includes mlx_xpm_file_to_image function
	to create a new image. It returns a pointer to the new image. Then we call mlx_get_data_addr
	function to get the address of the image. It returns a pointer to the image.
	
	Then we call mlx_new_window function to create a new window. It returns a pointer to
	the new window.
	
	mlx_mouse_hide() function hides the mouse cursor from the screen.

	void mlx_hook
	(mlx_win_list_t *win_ptr, int x_event, int x_mask, int (*f)(), void *param)
	Then we call mlx_hook function to register the hooks. 
	First hook is for ON_DESTROY event.
	When the window is closed, the program will call ft_exit_game function.
	Second hook is for ON_KEYDOWN event.
	When the key is pressed, the program will call ft_key_pressed function.

	Hooking into events is one of the most powerful tools that MiniLibX provides. 
	It allows you to register to any of the aforementioned events 
	with the call of a simple hook registration function.

	To achieve this, we call the function mlx_hook.
	2: ON_KEYDOWN -> For key press moment
	17: ON_DESTROY -> For window close moment little red button with cross

	mlx_loop_hook function is used to register a function to be called
	just before each new iteration of the event loop.

	mlx_loop_hook ( void *mlx_ptr, int (*funct_ptr)(), void *param );
	funct_ptr is a pointer to the function you want to be called when no event occurs.
	This assignment is specific to the window defined by the  win_ptr  identifier.  The
	param  adress  will be passed to the function everytime it is called, and should be used to
	store the parameters it might need.
	
	int mlx_loop ( void *mlx_ptr );
	To initiate a loop, we call the mlx_loop function with the mlx instance as only parameter.
	To receive events, you must use mlx_loop ().
	
*/
void	ft_game_render(t_dB *db)
{
	ft_map_db_control(db);
	db->pdx = cos(ft_degree_to_radian(db->pa));
	db->pdy = -1 * sin(ft_degree_to_radian(db->pa));
	if (db->is_key == '1')
	{
		db->sprite = '1';
		db->is_key = '0';
	}
	db->key_px = db->key_px + 0.5;
	db->key_py = db->key_py + 0.5;
	db->mlx = mlx_init();
	file_to_image(db);
	db->win = mlx_new_window(db->mlx, WIDTH, HEIGHT, "Cube3D");
	mlx_mouse_hide();
	mlx_hook(db->win, 17, 0, ft_exit_game, db);
	mlx_hook(db->win, 2, 0, ft_key_pressed, db);
	mlx_loop_hook(db->mlx, ft_game_start, db);
	mlx_loop(db->mlx);
}
