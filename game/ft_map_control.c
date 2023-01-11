/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bderya <bderya@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:08:55 by yogun             #+#    #+#             */
/*   Updated: 2023/01/11 13:49:53 by bderya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

/*
	This function checks if the map is closed properly by walls.
*/
void	ft_wall_control(char *s, t_dB *db)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	if (s[i] != '1')
		ft_error("Error! Map content is invalid!\n", db);
	while (s[i] == ' ' || s[i] == '1')
		i++;
	if (s[i] && s[i] != '\n')
		ft_error("Error! Map content is invalid!\n", db);
}

/*
	in this function we put doors and keys according to some
	patterns. We also check if the map is valid. For doors we 
	ask for a pattern like this:
		001
		101
		001
	In this pattern, automatically we assign the center of the
	pattern 'D' character for door.

	For keys we ask for a pattern like this:
		000
		000
		000
	Since, GNL reads the map line by line from top the bottom,
	key is placed as soon as proper pattern is being caught. So,
	most probably the key will be placed in the left top corner of
	the map. And so on...
*/
void	algorithm_door_key(char *s1, char *s2, char *s3, t_dB *db)
{
	int	i;

	i = db->zeros;
	if (s2[i - 1] == ' ' || s2[i + 1] == ' ' || !s2[i + 1]
		|| s2[i + 1] == '\n' || s1[i + 1] == '\n' || !s1[i + 1]
		|| s1[i - 1] == ' ' || s1[i + 1] == ' ' || s1[i] == ' '
		|| s3[i - 1] == ' ' || s3[i + 1] == ' ' || s3[i] == ' '
		|| s3[i + 1] == '\n' || !s3[i + 1])
		ft_error("Invalid Map!\n", db);
	if (s2[i] == '0' && s2[i + 1] == '1' && s2[i - 1] == '1'
		&& s1[i] == '0' && s3[i] == '0' && (s1[i + 1] == '1'
			|| s3[i + 1] == '1'))
		s2[i] = 'D';

	else if (db->is_key == '0' && s2[i] == '0' && s2[i - 1] == '0' 
			&& s2[i + 1] == '0' && s1[i - 1] == '0' && s1[i] == '0' 
			&& s1[i + 1] == '0' && s3[i] == '0' && s3[i + 1] == '0' 
			&& s3[i - 1] == '0')
	{
		db->is_key = '1';
		s2[i] = 'K';
		db->key_px = i;
	}
}

/*
	This function  positions the doors and keys in the map.
*/
void	ft_check_maplines(char *s, char *s2, char *s3, t_dB *db)
{
	int	i;

	i = 0;
	while (s2[i] && s2[i] == ' ')
		i++;
	if (s2[i] != '1')
		ft_error("Error! Map is invalid.\n", db);
	while (s2 && s2[i] && s2[i] != '\n')
	{
		while (s2[i] && (s2[i] == ' ' || s2[i] == '1'))
			i++;
		if (s2[i] && s2[i] != '\n')
		{
			db->zeros = i; // zeros is the positions of 0's in the line of the map
			//printf("zeros: %d\n", db->zeros);
			algorithm_door_key(s, s2, s3, db);
			i++;
		}
	}
}

/*
	This function checks if the map is closed properly by walls.
	With ft_check_maplines() function we also position the doors
	and the keys in the map. Y position of the key is placed there
	but X position is placed at the bottom of this function.
*/
void	ft_map_control(t_list	*map, t_dB *db)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = map->nxt; // nxt diye variable yok kontrol et
	if (!tmp)
		ft_error("Error! Map is invalid.\n", db);
	tmp2 = tmp->nxt;
	while (tmp)
	{
		if (map == db->map)
			ft_wall_control(map->content, db);
		if (tmp2 == NULL)
		{
			ft_wall_control(tmp->content, db);
			return ;
		}
		ft_check_maplines(map->content, tmp->content, tmp2->content, db);
		map = map->nxt;
		tmp = tmp->nxt;
		tmp2 = tmp2->nxt;
		if (db->is_key == '0')
		{
			db->key_py++;
		}	
	}
}
