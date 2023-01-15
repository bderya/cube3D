/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bderya <bderya@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 20:58:05 by yogun             #+#    #+#             */
/*   Updated: 2023/01/11 13:37:21 by bderya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

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

void	d_key(t_dB *db)
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
*/
int	ft_key_hook(int keyboard, t_dB *db)
{
	if (keyboard == 13)
		key_w(db);
	else if (keyboard == 0)
		key_a(db);
	else if (keyboard == 1)
		key_s(db);
	else if (keyboard == 2)
		d_key(db);
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
