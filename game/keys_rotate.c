/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bderya <bderya@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:28:15 by yogun             #+#    #+#             */
/*   Updated: 2023/01/11 13:54:30 by bderya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

/*
	Rotate point of view to the right direction
*/
void	right_key(t_dB *a)
{
	a->pa -= 5;
	a->pa = angle_to_360(a->pa);
	a->pdx = cos(ft_degree_to_radian(a->pa));
	a->pdy = -1 * sin(ft_degree_to_radian(a->pa));
}

/*
	Rotate point of view to the left direction
*/
void	left_key(t_dB *a)
{
	a->pa += 5;
	a->pa = angle_to_360(a->pa);
	a->pdx = cos(ft_degree_to_radian(a->pa));
	a->pdy = -1 * sin(ft_degree_to_radian(a->pa));
}

/*
	Door open and close function.
*/
void	key_e(t_dB *db)
{
	int		my;
	int		mx;

	mx = db->px + (db->pdx * 0.5);
	my = db->py + (db->pdy * 0.5);
	if (get_map_char(mx, my, db) == 'D' && db->is_key == '1')
	{
		// if (db->is_open == '1')
		// {
		// 	put_map_char(db->d_x, db->d_y, db, 'D');
		// 	printf("x\n");
		// }
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
