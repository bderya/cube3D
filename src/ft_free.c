/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bderya <bderya@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:15:48 by yogun             #+#    #+#             */
/*   Updated: 2023/01/30 19:28:50 by bderya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

/*
	This function frees map. tmp is a temporary variable.
*/
void	ft_lstfree(t_list *map)
{
	t_list	*tmp;

	if (!map)
		return ;
	tmp = map;
	while (map)
	{
		if (tmp->content)
			free(tmp->content);
		tmp->content = NULL;
		tmp = tmp->nxt;
		free(map);
		map = tmp;
	}
}

/*
	This function frees addr.
*/
void	ft_free_addr(char **addr)
{
	int	i;

	if (addr == NULL)
		return ;
	i = 0;
	while (i < 9)
	{
		free(addr[i]);
		addr[i] = NULL;
		i++;
	}
}

/*
	Ths function frees map, destroy image, free mlx, free addr and free line.
*/
void	ft_free(t_dB *db)
{
	ft_lstfree(db->map);
	if (db->img)
		mlx_destroy_image(db->mlx, db->img);
	free(db->mlx);
	ft_free_addr(db->addr);
	free(db->line);
	free(db->minimap);
	free(db->no);
	free(db->we);
	free(db->so);
	free(db->ea);
	free(db->door);
	free(db->key);
	free(db->key2);
}
