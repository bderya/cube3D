/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayogun <ayogun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 22:06:33 by yogun             #+#    #+#             */
/*   Updated: 2022/03/31 09:36:55 by ayogun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;
	size_t	j;
	size_t	ret;

	i = 0;
	j = 0;
	ret = ft_strlen(dst);
	len = size - 1;
	if (size > ret)
	{
		while (dst[i] != '\0')
			i++;
		while (src[j] != '\0' && j + i < len)
		{
			dst[i + j] = src[j];
			j++;
		}
		dst[i + j] = '\0';
		return (ret + ft_strlen(src));
	}
	return (ret + ft_strlen(src)+1);
}
