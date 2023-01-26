/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_horizontal_ray.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bderya <bderya@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:12:09 by yogun             #+#    #+#             */
/*   Updated: 2023/01/26 01:27:59 by bderya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

/*
	This function checks the distance horizontally. If the distance is less than
	the previous distance, we update the distance and zeros.
	Else, we update the position of the ray. 
*/
void	ft_horizontal_dist_check(t_dB *db, t_ray *ray, char c)
{
	double	disth;

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
	
	While depth is less than map height, we calculate the position of the ray.
	If the value of the map is 1 or D, we call ft_vertical_dist_check function.
	Because, it means there is an object in front of the ray and needs to be
	calculate the distance.
	
	Else, we continue to the next position of the ray until we reach the final wall
	or end of the map.

	P.S.: We use >> 6 which returns us the closest multiplier of 64. 
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

void	ft_horizontal_ray_sub2(t_dB *db, t_ray *ray)
{
	ray->depth = db->map_height;
	ray->rx = ray->px;
	ray->ry = ray->py;
}

/*
	In this function we calculate where the ray corssing with x axis.
	This function checks where the ray cross with first vertical line and position.
	
	In first if condition, we check if the ray is looking up. If it is,
	we calculate the position of the first horizontal line in accordance with.
	Then we calculate the position of the first horizontal line.

	In second if condition, we check if the ray is looking down. If it is,
	we calculate the position of the first horizontal line in accordance with.
	Then we calculate the position of the first horizontal line.

	In third if condition, we check if the ray is looking straight. If it is,
	we calculate the position of the first horizontal line in accordance with.
	Then we calculate the position of the first horizontal line.
	We substract small amount(0,0001) for accuracy. 

	Then we continue to the second part of the function...
*/
void	ft_horizontal_ray(t_dB *db, t_ray *ray)
{
	ray->atan_ra = 1.0 / tan(ft_degree_to_radian(ray->ra));
	ray->depth = 0;
	if (sin(ft_degree_to_radian(ray->ra)) > 0.0001)
	{
		ray->zerosh = 2;
		ray->ry = (((int)ray->py >> 6) << 6) - 0.0001;
		ray->rx = (ray->py - ray->ry) * ray->atan_ra + ray->px;
		ray->yo = -64;
		ray->xo = 64 * ray->atan_ra;
	}
	else if (sin(ft_degree_to_radian(ray->ra)) < -0.0001)
	{
		ray->zerosh = 3;
		ray->ry = (((int)ray->py >> 6) << 6) + 64;
		ray->rx = (ray->py - ray->ry) * ray->atan_ra + ray->px;
		ray->yo = 64;
		ray->xo = -64 * ray->atan_ra;
	}
	else if (sin(ft_degree_to_radian(ray->ra)) < 0.0001 && \
		sin(ft_degree_to_radian(ray->ra)) > -0.0001)
	{
		ft_horizontal_ray_sub2(db, ray);
	}
	ft_horizontal_ray_2(db, ray);
}

/*
	This function do ray cast math. Again, for more information please check:
	https://lodev.org/cgtutor/raycasting.html

	We use this function to draw the walls and sprites acccording to the angle
	of the players view.

	First we calculate the angle of the ray. We add 30 to the player's angle
	because we want to draw 60 degree view. Then we calculate the vertical
	and horizontal ray's distance. We use the distance to draw the walls
	and sprites. We also use the distance to fix the fisheye effect.
	We also use the distance to calculate the height of the walls and sprites.
	
	While i is less than WIDTH we draw the walls and sprites. With the help of
	ft_vertical_ray and ft_horizontal_ray functions we calculate where the
	ray is crossing first time with horizontal or the vertical line.

	This function is used to fix fish eye effect:
		db->dist = db->dist * cos(ft_degree_to_radian
			(angle_to_360(db->pa - ray->ra)));
	
	If we look right or left, we take vertical ray's Y position:
		db->ray = (int)(ray->vy) % 64;
	
	Else, we take horizontal ray's X position:
		db->ray = (int)(ray->vx) % 64;
	
	With line_draw function we draw the walls and doors.
	With sprite_draw function we draw the sprites.
	Finally, we reset the ray's angle and increase i.
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
		db->dist = (db->dist
				* cos(ft_degree_to_radian(angle_to_360(db->pa - ray->ra))));
		if (db->zeros > 3 && db->zeros != 6)
			db->ray = (int)(ray->vy) % 64;
		else
			db->ray = (int)(ray->rx) % 64;
		line_draw(db, i);
		sprite_draw(db, i);
		ray->ra = angle_to_360(ray->ra - db->angle);
		i++;
	}
}
