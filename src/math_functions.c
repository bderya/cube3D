/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bderya <bderya@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 08:35:00 by yogun             #+#    #+#             */
/*   Updated: 2023/01/11 13:57:02 by bderya           ###   ########.fr       */
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
