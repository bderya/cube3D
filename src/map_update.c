/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:23:10 by yogun             #+#    #+#             */
/*   Updated: 2023/01/16 19:29:46 by yogun            ###   ########.fr       */
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
	In this function we read from the map the char value
	from the place where the player is located currently.
	
	111
	1e1
	111
	
	In this map above, the player is located at the place
	where the 'e' is. So we read the map and get the value
	which is 'e' and return it.
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
