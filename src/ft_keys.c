/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 20:58:05 by yogun             #+#    #+#             */
/*   Updated: 2023/01/23 10:55:31 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

/*
	In this function we wrote the things will happen when we click
	the 'A' button. Hence, when we click, our player current position is increased 
	0,2 time player's cos or sin component. We get this value into
	my and mx. This value is not the exact value of the player's
	current position. It is player's effective area kind of.
	This is why we use 0,2 rather than 0,1. 
	Because it provides us, for instance collect the key 0,1 before
	the location of the key. So we can collect the key.
	
	With get_map_char() we get from the map the char value
	from the place where the player is located currently and pack
	it into <val> variable.
	
	Then we check if the value is '0' or 'K'. If it is '0' we can
	move the player. If it is 'K' we can move the player and also
	we can get the key. So we set the is_key variable to '1' and
	we set the sprite variable to '0' and we put the map char
	to '0' with put_map_char() function. This deletes the key
	sprite from the map and we write '0' to the map. Also we update
	is_key variable in our db to '1' to show that we have the key.

	Unless the value is '0' we move the player. We increase the
	player's current position with 0,1 time player's cos or sin
	component. If the player is moving we increase the step_num
	variable to show that the player is moving.
*/
void	key_a(t_dB *db)
{
	int		my;
	int		mx;
	char	val;

	mx = db->px + (db->pdy * 0.2);
	my = db->py - (db->pdx * 0.2);
	val = get_map_char(mx, my, db);
	if (val == '0' || val == 'K')
	{
		if (val == 'K')
		{
			db->is_key = '1';
			db->sprite = '0';
			put_map_char(mx, my, db, '0');
		}
		db->px += (db->pdy * 0.1);
		db->py -= (db->pdx * 0.1);
		if (db->step_num)
			db->step_num += 1;
	}
}

/*
	In this function we wrote the things will happen when we click
	the 'W' button. Hence, when we click, our player current position is increased 
	0,2 time player's cos or sin component. We get this value into
	my and mx. This value is not the exact value of the player's
	current position. It is player's effective area kind of. This is why we use 0,2 rather
	than 0,1. Because it provides us, for instance collect the key 0,1 before
	the location of the key. So we can collect the key.
	
	With get_map_char() we get from the map the char value
	from the place where the player is located currently and pack
	it into <val> variable.
	
	Then we check if the value is '0' or 'K'. If it is '0' we can
	move the player. If it is 'K' we can move the player and also
	we can get the key. So we set the is_key variable to '1' and
	we set the sprite variable to '0' and we put the map char
	to '0' with put_map_char() function. This deletes the key
	sprite from the map and we write '0' to the map. Also we update
	is_key variable in our db to '1' to show that we have the key.

	Unless the value is '0' we move the player. We increase the
	player's current position with 0,1 time player's cos or sin
	component. If the player is moving we increase the step_num
	variable to show that the player is moving.
*/
void	key_w(t_dB *db)
{
	int		my;
	int		mx;
	char	val;
	
	mx = db->px + (db->pdx * 0.2);
	my = db->py + (db->pdy * 0.2);
	val = get_map_char(mx, my, db);
	if (val == '0' || val == 'K')
	{
		if (val == 'K')
		{
			db->is_key = '1';
			db->sprite = '0';
			put_map_char(mx, my, db, '0');
		}
		db->px += (db->pdx * 0.1);
		db->py += (db->pdy * 0.1);
		if (db->step_num)
			db->step_num += 1;
	}
}

/*
	In this function we wrote the things will happen when we click
	the 'D' button. Hence, when we click, our player current position is increased 
	0,2 time player's cos or sin component. We get this value into
	my and mx. This value is not the exact value of the player's
	current position. It is player's effective area kind of. This is why we use 0,2 rather
	than 0,1. Because it provides us, for instance collect the key 0,1 before
	the location of the key. So we can collect the key.
	
	With get_map_char() we get from the map the char value
	from the place where the player is located currently and pack
	it into <val> variable.
	
	Then we check if the value is '0' or 'K'. If it is '0' we can
	move the player. If it is 'K' we can move the player and also
	we can get the key. So we set the is_key variable to '1' and
	we set the sprite variable to '0' and we put the map char
	to '0' with put_map_char() function. This deletes the key
	sprite from the map and we write '0' to the map. Also we update
	is_key variable in our db to '1' to show that we have the key.

	Unless the value is '0' we move the player. We increase the
	player's current position with 0,1 time player's cos or sin
	component. If the player is moving we increase the step_num
	variable to show that the player is moving.
*/
void	key_d(t_dB *db)
{
	int		my;
	int		mx;
	char	val;

	mx = db->px - (db->pdy * 0.2);
	my = db->py + (db->pdx * 0.2);
	val = get_map_char(mx, my, db);
	if (val == '0' || val == 'K')
	{
		if (val == 'K')
		{
			db->is_key = '1';
			db->sprite = '0';
			put_map_char(mx, my, db, '0');
		}
		db->px -= (db->pdy * 0.1);
		db->py += (db->pdx * 0.1);
		if (db->step_num)
			db->step_num += 1;
	}
}

/*
	In this function we wrote the things will happen when we click
	the 'S' button. Hence, when we click, our player current position is increased 
	0,2 time player's cos or sin component. We get this value into
	my and mx. This value is not the exact value of the player's
	current position. It is player's effective area kind of. This is why we use 0,2 rather
	than 0,1. Because it provides us, for instance collect the key 0,1 before
	the location of the key. So we can collect the key.
	
	With get_map_char() we get from the map the char value
	from the place where the player is located currently and pack
	it into <val> variable.
	
	Then we check if the value is '0' or 'K'. If it is '0' we can
	move the player. If it is 'K' we can move the player and also
	we can get the key. So we set the is_key variable to '1' and
	we set the sprite variable to '0' and we put the map char
	to '0' with put_map_char() function. This deletes the key
	sprite from the map and we write '0' to the map. Also we update
	is_key variable in our db to '1' to show that we have the key.

	Unless the value is '0' we move the player. We increase the
	player's current position with 0,1 time player's cos or sin
	component. If the player is moving we increase the step_num
	variable to show that the player is moving.
*/
void	key_s(t_dB *db)
{
	int		my;
	int		mx;
	char	val;

	mx = db->px - (db->pdx * 0.2);
	my = db->py - (db->pdy * 0.2);
	val = get_map_char(mx, my, db);
	if (val == '0' || val == 'K')
	{
		if (val == 'K')
		{
			db->is_key = '1';
			db->sprite = '0';
			put_map_char(mx, my, db, '0');
		}
		db->px -= (db->pdx * 0.1);
		db->py -= (db->pdy * 0.1);
		if (db->step_num)
			db->step_num += 1;
	}
}

/*
	In this function we define the keys that will be hooked.
	W,A,S,D are the keys for moving the player.
	E is the key for opening the door.
	ESC is the key for exiting the game.
	Left and right arrow keys are for rotating the player.
*/
int	ft_key_pressed(int keyboard, t_dB *db)
{
	if (keyboard == 13)
		key_w(db);
	else if (keyboard == 0)
		key_a(db);
	else if (keyboard == 1)
		key_s(db);
	else if (keyboard == 2)
		key_d(db);
	else if (keyboard == 14)
		key_e(db);
	else if (keyboard == 53)
		ft_exit_game(db);
	else if (keyboard == 123)
		left_key(db);
	else if (keyboard == 124)
		right_key(db);
	return (0);
}
