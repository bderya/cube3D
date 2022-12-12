/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_format_ok.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 21:51:44 by yogun             #+#    #+#             */
/*   Updated: 2022/12/11 21:52:27 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map_format_ok(char *str, char *str2)
{
	int	counter;

	counter = 0;
	while (ft_strlen(str) != 4 && str)
		str++;
	if (!str || *str == '\0')
		return (0);
	while (str[counter])
	{
		if (str[counter] != str2[counter])
			return (0);
		counter+=1;
	}
	return (1);
}