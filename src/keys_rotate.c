/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bderya <bderya@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:28:15 by yogun             #+#    #+#             */
/*   Updated: 2023/01/25 12:11:43 by bderya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

/*
	Rotate point of view to the right direction
*/
void	right_key(t_dB *db)
{
	db->pa -= 5;
	db->pa = angle_to_360(db->pa);
	db->pdx = cos(ft_degree_to_radian(db->pa));
	db->pdy = -1 * sin(ft_degree_to_radian(db->pa));
}

/*
	Rotate point of view to the left direction
*/
void	left_key(t_dB *db)
{
	db->pa += 5;
	db->pa = angle_to_360(db->pa);
	db->pdx = cos(ft_degree_to_radian(db->pa));
	db->pdy = -1 * sin(ft_degree_to_radian(db->pa));
}

/*
	Door open and close function.
	
	In this function we wrote the things will happen when we click
	the 'E' button. Hence, when we click, our player current position is 
	increased 0,5 time player's cos or sin component. We get this value into
	my and mx. This value is not the exact value of the player's
	current position. It is the value of the place where the player
	will be located after the movement. This provides us, for instance
	open the door 0,5 before the location of the door. So we can open the door
	a bit earlier.

	In if condition, we check if the player's effective area is on the door
	location
	and if the player has already collected the key. If the player has the key, 
	we open the door and change the door location to '0' in the map.
	We also change the is_open variable to '1' to indicate that the door is open.
	We also change the step_num variable to 1 to indicate that step_num counter
	has been reseted. We use this value to close the door after a certain
	amount of steps. Also to save the door location, we use d_x and d_y variables 
	in database.
	
	In else if condition, we check if the player's effective area is on the door 
	location and has the key and the door is open: then we close the door and 
	change the door location to 'D' in the map. We also change the is_open variable 
	to '0' to indicate that the door is closed.
*/
void	key_e(t_dB *db)
{
	int		my;
	int		mx;

	mx = db->px + (db->pdx * 0.5);
	my = db->py + (db->pdy * 0.5);
	if (get_map_char(mx, my, db) == 'D' && db->is_key == '1')
	{
		db->d_x = mx;
		db->d_y = my;
		put_map_char(mx, my, db, '0');
		db->is_open = '1';
		db->step_num = 1;
	}
	else if (mx == db->d_x && my == db->d_y && db->is_key == '1'
		&& ((int)db->px != db->d_x || (int)db->py != db->d_y))
	{
		if (db->is_open == '1')
		{
			db->is_open = '0';
			put_map_char(mx, my, db, 'D');
		}
	}
}
