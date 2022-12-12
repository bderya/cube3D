/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:54:58 by yogun             #+#    #+#             */
/*   Updated: 2022/12/12 16:35:09 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	This function checks if the given texture paths and 
	give the relevant path to t_dB struct.
*/
void	texture_check(t_dB *data, char *line, char c)
{
	char	*tmp;

	if ((c == 'N' && data->no) || (c == 'S' && data->so)
		|| (c == 'W' && data->we) || (c == 'E' && data->ea))
		error_print("Multiple texture pathes for one instance!\n", data);
	tmp = ft_strtrim(line, "\n");
	if (c == 'N')
		data->no = ft_strtrim(tmp, " ");
	else if (c == 'S')
		data->so = ft_strtrim(tmp, " ");
	else if (c == 'W')
		data->we = ft_strtrim(tmp, " ");
	else
		data->ea = ft_strtrim(tmp, " ");
	free(tmp);
}

/*
	This function checks if the given colour values are valid.
	It checks if the comma used in correct place and if the
	color values are three piece and after them comes empty space
	or new line or tabulation.
*/
int	color_check_2(char *line, int i, t_dB *data)
{
	int	j;

	j = 0;
	while (line[j] && line[j] != ','
		&& (ft_isdigit(line[j]) || line[j] == ' ' || line[j] == '\t'))
		j++;
	if (i < 2 && line[j] != ',')
		error_print("Unknown color value\n", data);
	if (i == 2 && line[j] && line[j] != '\n'
		&& line[j] != ' ' && line[j] != '\t')
		error_print("Unknown color value\n", data);
	return (j);
}

/*
	This function checks if the given colour values are valid.
*/
void	color_check(t_dB *data, char *line, char c)
{
	int		i;
	char	*sub;
	int		j;

	j = 0;
	while (line && (*line == ' ' || *line == '\t'))
		line++;
	while (j < 3)
	{
		i = color_check_2(line, j, data);
		sub = ft_substr(line, 0, i);
		if (line[i] == ',')
			line++;
		line =+ i;
		i = ft_atoi(sub);
		free(sub);
		if (i >= 256 || i <= -1)
			error_print("Unknown color value\n", data);
		if (c == 'C')
			data->c[j] = i;
		else if (c == 'F')
			data->f[j] = i;
		j++;
	}
}

////////////

int	ft_map_line_check(char *line, t_dB *data)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
		{
			if (data->player != '\0')
				error_print("Only one player at a time!\n", data);
			data->player = line[i];
			data->px = i + 0.5;
			data->py = data->map_height + 0.5;
			line[i] = '0';
		}
		else if (line[i] != ' ' && line[i] != '1' && line[i] != '0')
			error_print("Map is invalid!\n", data);
		i++;
	}
	return (i);
}

void	ft_map_init(char *line, t_dB *data, int fd)
{
	int		i;

	while (line)
	{
		i = 0;
		while (line[i] && line[i] == ' ')
			i++;
		if (!line[i] || line[i] == '\n')
		{
			free(line);
			data->line = NULL;
			break ;
		}
		i = ft_map_line_check(line, data);
		if (i > data->map_width)
			data->map_width = i;
		ft_lstadd_back(&data->map, ft_lstnew(ft_strtrim(line, "\n")));
		free(line);
		data->line = NULL;
		line = get_next_line(fd);
		data->map_height++;
	}
	// To be continued... For more information look at page 57 in the notebook.
}