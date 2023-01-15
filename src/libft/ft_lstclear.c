/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 23:35:26 by yogun             #+#    #+#             */
/*   Updated: 2023/01/07 15:06:36 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*n1;
	t_list	*n2;

	if (!lst)
		return ;
	n1 = *lst;
	while (n1)
	{
		n2 = n1->nxt;
		free(n1);
		n1 = n2;
	}
	*lst = NULL;
}
