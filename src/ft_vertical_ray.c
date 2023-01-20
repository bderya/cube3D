/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vertical_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:10:56 by yogun             #+#    #+#             */
/*   Updated: 2023/01/17 17:31:16 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

/*
	This function checks the distance vertically. 
*/
void	ft_vertical_dist_check(t_dB *db, t_ray *ray, char c)
{
	db->dist = calculate_distance(ray);
	db->zeros = ray->zeros;
	if (c == 'D')
		db->zeros = 6;
	ray->depth = db->map_width;
}

/*
	This function is the second part.
	
	While depth is less than map width, we calculate the position of the ray.
	If the value of the map is 1 or D, we call ft_vertical_dist_check function.
	Because, it means there is an object in front of the ray and needs to be
	calculate the distance.
	
	Else, we continue to the next position of the ray until we reach the final wall
	or end of the map.

	P.S.: We use >> 6 which returns us the closest multiplier of 64.  
*/
void	ft_vertical_ray_2(t_dB *db, t_ray *ray)
{
	int		mx;
	int		my;
	char	val;

	while (ray->depth < db->map_width)
	{
		mx = (int)ray->rx >> 6;
		my = (int)ray->ry >> 6;
		val = get_map_char(mx, my, db);
		if (val == '1' || val == 'D')
			ft_vertical_dist_check(db, ray, val);
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->depth += 1;
		}
	}
	ray->vx = ray->rx;
	ray->vy = ray->ry;
}

/*
	This function checks where the ray cross with first vertical line and position.
	
	In first if condition, we check if the ray is looking right. 
	If it is, we calculate the position of the first vertical line in accordance with. 
	Then we calculate the position of the first vertical line.

	In second if condition, we check if the ray is looking left. 
	If it is, we calculate the position of the first vertical line in accordance with. 
	Then we calculate the position of the first vertical line.

	In third if condition, we check if the ray is looking straight. If so,
	we set the depth to the map width and return.
	
	Then we continue to the second part of the function...
*/
void	ft_vertical_ray(t_dB *db, t_ray *ray)
{
	ray->tan_ra = tan(ft_degree_to_radian(ray->ra));
	ray->depth = 0;
	if (cos(ft_degree_to_radian(ray->ra)) > 0.0001)
	{
		ray->zeros = 5;
		ray->rx = (((int)ray->px >> 6) << 6) + 64;
		ray->ry = (ray->px - ray->rx) * ray->tan_ra + ray->py;
		ray->xo = 64;
		ray->yo = -64 * ray->tan_ra;
	}
	else if (cos(ft_degree_to_radian(ray->ra)) < -0.0001)
	{
		ray->zeros = 4;
		ray->rx = (((int)ray->px >> 6) << 6) - 0.0001;
		ray->ry = (ray->px - ray->rx) * ray->tan_ra + ray->py;
		ray->xo = -64;
		ray->yo = 64 * ray->tan_ra;
	}
	else if (cos(ft_degree_to_radian(ray->ra)) == 0)
	{
		ray->depth = db->map_width;
		ray->rx = ray->px;
		ray->ry = ray->py;
	}
	ft_vertical_ray_2(db, ray);
}
