/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bderya <bderya@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 16:13:19 by yogun             #+#    #+#             */
/*   Updated: 2023/01/11 13:22:29 by bderya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

/*
	This function prints an error message and exits the program,
	freeing(with ft_free function) all the allocated memory and 
	also printing "Error" to the standard error output.
*/
void	ft_error(char *str, t_dB *db)
{
	ft_free(db);
	write(2, "Error\n", 6);
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}
