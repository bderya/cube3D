/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 22:02:26 by yogun             #+#    #+#             */
/*   Updated: 2023/01/10 17:41:57 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	ft_wall_minimap(t_dB *db, int x, int y, int k)
{
	int	j;
	int	i;

	i = 0;
	while (i <= WIDTH / 50)
	{
		j = 0;
		while (j <= HEIGHT / 50)
		{
			if (i == 0 || j == 0)
				my_mlx_pixel_put_mini(db, i + x * WIDTH / 50,
					j + y * HEIGHT / 50, 0x0FF000000);
			else
				my_mlx_pixel_put_mini(db, i + x * WIDTH / 50,
					j + y * HEIGHT / 50, k);
			j++;
		}
		i++;
	}
}

void	ft_player_minimap(t_dB *db, double x, double y)
{
	double	j;
	double	i;

	i = 0.5 - WIDTH / 250;
	while (i <= WIDTH / 250)
	{
		j = 0.5 - HEIGHT / 250;
		while (j <= WIDTH / 250)
		{
			my_mlx_pixel_put_mini(db, i + x * WIDTH / 50,
				j + y * HEIGHT / 50, 0xFFFF31);
			j++;
		}
		i++;
	}
}

void	ft_player_init(t_dB *db)
{
	double	x;
	double	y;

	if (db->px < 5)
		x = db->px;
	else if (db->map_width - db->px < 5)
		x = 10 - (db->map_width - db->px);
	else
		x = 4 + (db->px - (int)db->px);
	if (db->py < 5)
		y = db->py;
	else if (db->map_height - db->py < 5)
		y = 10 - (db->map_height - db->py);
	else
		y = 5 + (db->py - (int)db->py);
	ft_player_minimap(db, x, y);
}

void	ft_sub_minimap(t_list *map, t_dB *db, double x)
{
	int		i;
	int		j;
	char	*line;

	j = 0;
	while (map && j < 10)
	{
		line = map->content;
		i = 0;
		while (line[(int)x + i] && i < 10)
		{
			if (line[(int)x + i] == '1')
				ft_wall_minimap(db, i, j, 0x13AED4);
			else if (line[(int)x + i] == 'D')
				ft_wall_minimap(db, i, j, 0xAE8039);
			else
				ft_wall_minimap(db, i, j, 0x00000000);
			i++;
		}
		j++;
		map = map->nxt;
	}
	ft_player_init(db);
}

void	ft_minimap_render(t_list *map, t_dB *db)
{
	double	y;
	double	x;

	if (db->minimap)
		mlx_destroy_image(db->mlx, db->minimap);
	db->minimap = mlx_new_image(db->mlx, WIDTH / 5, HEIGHT / 5);
	db->addr[1] = mlx_get_data_addr(db->minimap, &db->bits_per_pixel[0],
			&db->line_length[0], &db->endian[0]);
	y = 0;
	while (db->map_height > 11 && db->py > y + 6 && db->map_height > y + 10)
	{
		map = map->nxt;
		y++;
	}
	if (db->map_width < 11 || db->px <= 4)
		x = 0;
	else if (db->map_width - db->px <= 6)
		x = db->map_width - 10;
	else
		x = db->px - 4;
	ft_sub_minimap(map, db, x);
	mlx_put_image_to_window(db->mlx, db->win, db->minimap, 0, 0);
}
