/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bderya <bderya@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:23:10 by yogun             #+#    #+#             */
/*   Updated: 2023/01/11 13:56:29 by bderya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"	
/*
	Because of player moved and changed location, we update the map
	according to current status whic we got from get_map_char.
*/
void	put_map_char(int mx, int my, t_dB *db, char c)
{
	char	*str;
	t_list	*map;

	if (mx < 0 || my < 0)
		return ;
	map = db->map;
	while (my > 0)
	{
		my--;
		map = map->nxt;
	}
	str = map->content;
	str[mx] = c;
}

/*
	In this function we read from the map the place where the
	player is located currently.
*/
char	get_map_char(int mx, int my, t_dB *db)
{
	t_list	*map;
	char	*s;

	if (mx < 0 || my < 0 || mx >= db->map_width || my >= db->map_height)
		return (' ');
	map = db->map;
	while (my > 0)
	{
		my--;
		map = map->nxt;
	}
	s = map->content;
	return (s[mx]);
}
