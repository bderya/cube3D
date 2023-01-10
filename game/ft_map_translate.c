/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_translate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 08:05:48 by yogun             #+#    #+#             */
/*   Updated: 2023/01/07 10:14:00 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

/*
	This function is used to packa all the information from the map into the db.
*/
void	ft_textures_read(t_dB *db, char *line, char c)
{
	char	*tmp;

	if ((c == 'N' && db->no) || (c == 'S' && db->so)
		|| (c == 'W' && db->we) || (c == 'E' && db->ea))
		ft_error("Error! One texture has been assigned more than one picture.\n", db);
	tmp = ft_strtrim(line, "\n");
	if (c == 'N')
		db->no = ft_strtrim(tmp, " ");
	else if (c == 'S')
		db->so = ft_strtrim(tmp, " ");
	else if (c == 'W')
		db->we = ft_strtrim(tmp, " ");
	else if (c == 'E')
		db->ea = ft_strtrim(tmp, " ");
	free(tmp);
}

/*
	This function is second part as the name indicates.
	It checks if the RGB values are valid. If not, it throws an error.
	If in first two values of RGB, there is no comma, it throws an error.
	If in third value of RGB, there isn't a space, tab or new line it throws an error.
*/
int	ft_floorceiling_read_2(char *line, int j, t_dB *a)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ','
		&& (ft_isdigit(line[i]) || line[i] == ' ' || line[i] == '\t'))
		i++;
	if (j < 2 && line[i] != ',')
		ft_error("Error! RGB format is invalid.\n", a);
	if (j == 2 && line[i] && line[i] != '\n'
		&& line[i] != ' ' && line[i] != '\t')
		ft_error("Error! RGB format is invalid.\n", a);
	return (i);
}

/*
	This function is used to pack RGB color values from the map into the db.
	Such as db->c for ceiling and db->f for floor. They are both int arrays.
*/
void	ft_floorceiling_read(t_dB *db, char *line, char c)
{
	int		i;
	char	*tmp;
	int		j;

	j = 0;
	while (line && (*line == ' ' || *line == '\t'))
		line++;
	while (j < 3)
	{
		i = ft_floorceiling_read_2(line, j, db);
		tmp = ft_substr(line, 0, i);
		if (line[i] == ',')
			line++;
		line = line + i;
		i = ft_atoi(tmp);
		free(tmp);
		if (i > 255 || i < 0)
			ft_error("Error! Colour value can be in between 0-255\n", db);
		if (c == 'C')
			db->c[j] = i;
		else if (c == 'F')
			db->f[j] = i;
		j++;
	}
}

/*
	This function char by char checks if the line is a valid map line.
	Line is the string that comes from GNL.
*/
void	ft_map_translate(t_dB *a, char *line, int fd)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;	
	if (line[i] == 'N' && line[i + 1] == 'O')
		ft_textures_read(a, line + 2, 'N');
	else if (line[i] == 'S' && line[i + 1] == 'O')
		ft_textures_read(a, line + 2, 'S');
	else if (line[i] == 'W' && line[i + 1] == 'E')
		ft_textures_read(a, line + i + 2, 'W');
	else if (line[i] == 'E' && line[i + 1] == 'A')
		ft_textures_read(a, line + i + 2, 'E');
	else if (line[i] == 'F')
		ft_floorceiling_read(a, line + i + 1, 'F');
	else if (line[i] == 'C')
		ft_floorceiling_read(a, line + i + 1, 'C');
	else if (line[i] == '1')
		ft_map_init(line, a, fd);
	else if (line[i] && line[i] != '\n')
		ft_error("Map is invalid!\n", a);
}
