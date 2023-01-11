/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_horizontal_ray.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bderya <bderya@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:12:09 by yogun             #+#    #+#             */
/*   Updated: 2023/01/11 13:35:48 by bderya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	ft_horizontal_dist_check(t_dB *db, t_ray *ray, char c)
{
	double	disth;// we use this variable to store // Hya burada

	disth = calculate_distance(ray);
	if (disth < db->dist)
	{
		db->zeros = ray->zerosh;
		if (c == 'D')
			db->zeros = 6;
		db->dist = disth;
	}
	else
	{
		ray->rx = ray->vx;
		ray->ry = ray->vy;
	}
	ray->depth = db->map_height;
}

/*
	This function is the second part.
*/
void	ft_horizontal_ray_2(t_dB *db, t_ray *ray)
{
	int		mx;
	int		my;
	char	c;

	while (ray->depth < db->map_height)
	{
		mx = (int)ray->rx >> 6;
		my = (int)ray->ry >> 6;
		c = get_map_char(mx, my, db);
		if (c == '1' || c == 'D')
			ft_horizontal_dist_check(db, ray, c);
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->depth += 1;
		}
	}
}

/*
	In this function we calculate where the ray corssing with x axis
*/
void	ft_horizontal_ray(t_dB *db, t_ray *ray)
{
	ray->atan_ra = 1.0 / tan(ft_degree_to_radian(ray->ra));
	ray->depth = 0;
	if (sin(ft_degree_to_radian(ray->ra)) > 0.0001)// we check if the Ray is facing up
	{
		ray->zerosh = 2;
		ray->ry = (((int)ray->py >> 6) << 6) - 0.0001;// we round the Ray's Y position to the nearest 64th value
		// we substract small amount for accuracy
		ray->rx = (ray->py - ray->ry) * ray->atan_ra + ray->px;
		ray->yo = -64;
		ray->xo = 64 * ray->atan_ra;
	}
	else if (sin(ft_degree_to_radian(ray->ra)) < -0.0001)// or down
	{
		ray->zerosh = 3;
		ray->ry = (((int)ray->py >> 6) << 6) + 64;
		ray->rx = (ray->py - ray->ry) * ray->atan_ra + ray->px;
		ray->yo = 64;
		ray->xo = -64 * ray->atan_ra;
	}
	else if (sin(ft_degree_to_radian(ray->ra)) < 0.0001 && \
		sin(ft_degree_to_radian(ray->ra)) > -0.0001)// or straight //Comment error burasi tamamdir
	{
		ray->depth = db->map_height;
		ray->rx = ray->px;
		ray->ry = ray->py;
	}
	ft_horizontal_ray_2(db, ray);
}

/*
	This function do ray cast math.
*/
void	ft_ray_cast(t_dB *db, t_ray *ray)
{
	int		i;

	ray->ra = angle_to_360(db->pa + 30);
	i = 0;
	ray->px = db->px * 64;
	ray->py = db->py * 64;
	while (i < WIDTH)
	{
		db->dist = 1000000; 
		ft_vertical_ray(db, ray);
		ft_horizontal_ray(db, ray);
		db->dist = db->dist * cos(ft_degree_to_radian \ 
			(angle_to_360(db->pa - ray->ra))); // we use this to fix fisheye effect
		if (db->zeros > 3 && db->zeros != 6)
			db->ray = (int)(ray->vy) % 64; // if we look right or left we take vertical ray's Y position
		else
			db->ray = (int)(ray->rx) % 64;	// if we look up or down we take horizontal ray's X position
		line_draw(db, i);
		sprite_draw(db, i);
		ray->ra = angle_to_360(ray->ra - db->angle);
		i++;
	}
}
