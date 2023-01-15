/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 23:36:13 by ayogun            #+#    #+#             */
/*   Updated: 2023/01/07 15:06:36 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*nxt;

	if (lst != NULL)
	{
		nxt = lst;
		while (1)
		{
			(*f)(nxt->content);
			nxt = nxt->nxt;
			if (nxt == NULL)
				return ;
		}
	}
}
