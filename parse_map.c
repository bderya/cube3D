/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 22:03:32 by yogun             #+#    #+#             */
/*   Updated: 2022/12/12 15:48:18 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	This function checks if the given texture paths and 
	give the relevant path to t_dB struct. If so, it 
	invokes the relevant function.
*/

void	ft_check_parameters(t_dB *data, char *line, int fd)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O')
		texture_check(data, line + 2, 'N');
	else if (line[i] == 'S' && line[i + 1] == 'O')
		texture_check(data, line + 2, 'S');
	else if (line[i] == 'W' && line[i + 1] == 'E')
		texture_check(data, line + i + 2, 'W');
	else if (line[i] == 'E' && line[i + 1] == 'A')
		texture_check(data, line + i + 2, 'E');
	else if (line[i] == 'F')
		color_check(data, line + i + 1, 'F');
	else if (line[i] == 'C')
		color_check(data, line + i + 1, 'C');
	else if (line[i] == '1')
		ft_map_init(line, data, fd);
	else if (line[i] && line[i] != '\n')
		ft_error("Invalid map!\n", data);
}

/*
	This function open the given file and checks if the
	file is valid. If so, it reads the file line by line.
*/
void	ft_map_process(t_dB *data, char *argv)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		error_print("Error! File or directory couldn't be found\n", data);
	data->line = get_next_line(fd);
	if (!data->line)
		error_print("Map is not valid!\n", data);
	while (data->line)
	{
		ft_check_parameters(data, data->line, fd);
		if (!data->line)
			break ;
		free(data->line);
		data->line = get_next_line(fd);
	}
	close(fd);
	if (data->map == NULL)
		error_print("Map pattern does not found in the file!\n", data);
}
