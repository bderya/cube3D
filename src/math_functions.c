/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 08:35:00 by yogun             #+#    #+#             */
/*   Updated: 2023/01/17 17:53:20 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

/*
	This function converts degree to radian. 
	PI is taken into account as 3.14159.
*/
double	ft_degree_to_radian(double degree)
{
	return (degree * 3.14159 / 180.0);
}
/*
	This function converts minus degrees to positive degrees.
	Also converts degrees greater than 360 to degrees between 0 and 360.
*/
double	angle_to_360(double degree)
{
	if (degree >= 360)
		degree = degree - 360;
	else if (degree <= -1)
		degree = degree + 360;
	return (degree);
}

/*
	This function calculates the distance between the player and the object.
*/
double	calculate_distance(t_ray *ray)
{
	double	x;

	x = cos(ft_degree_to_radian(ray->ra)) * (ray->rx - ray->px)
		- sin(ft_degree_to_radian(ray->ra)) * (ray->ry - ray->py);
	return (x);
}
