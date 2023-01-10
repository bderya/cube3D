/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:26:42 by yogun             #+#    #+#             */
/*   Updated: 2023/01/08 08:13:41 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

/*
	This function completes the map to the height of 10 if it is less than 10.
	It fills the map with spaces until it is 10 rows.
*/
void	fill_with_rows(t_dB *db)
{
	char	*tmp;
	int		i;

	while (db->map_height < 10)
	{
		i = 0;
		tmp = malloc(db->map_width + 1);
		while (i < db->map_width)
		{
			tmp[i] = ' ';
			i++;
		}
		tmp[i] = '\0';
		ft_lstadd_back(&db->map, ft_lstnew(tmp));
		db->map_height++;
	}
}

/*
	In this function we fill the map with spaces if it is not
	complete to the width of the map.
*/
void	complete_to_rect(t_list *map, t_dB *db)
{
	char	*tmp;

	if (db->map_width < 10)
		db->map_width = 10;
	while (map)
	{
		while ((int)ft_strlen(map->content) < db->map_width)
		{
			tmp = map->content;
			map->content = ft_strjoin(map->content, " ");
			free(tmp);
		}
		map = map->nxt;
	}
	if (db->map_height < 10)
		fill_with_rows(db);
}

/*
	This function is used to check if the map is valid and it 
	gets the player position and direction.
*/
int	ft_player_position(char *line, t_dB *db)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
		{
			if (db->player != '\0')
				ft_error("Error! Only one player is allowed in map file.\n", db);
			db->player = line[i];
			db->px = i + 0.5;
			db->py = db->map_height + 0.5;
			line[i] = '0';
		}
		else if (line[i] != ' ' && line[i] != '1' && line[i] != '0')
			ft_error("Error! Unknown character is found in the map file.\n", db);
		i++;
	}
	return (i);
}

/*
	This function is used to check if the map is valid.
	It checks if the map is a rectangle and if the map is surrounded by walls. 
	If the map is not valid, it will throw an error.
	Here it also gets the map width and height.
	Also under the ft_map_control function, we place doors and keys.
	We fill the empty spaces in the map. For further information,
	check regarding functions.
*/
void	ft_map_init(char *line, t_dB *db, int fd)
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
			db->line = NULL;
			break ;
		}
		i = ft_player_position(line, db);
		if (i > db->map_width)
			db->map_width = i;
		ft_lstadd_back(&db->map, ft_lstnew(ft_strtrim(line, "\n")));
		free(line);
		db->line = NULL;
		line = get_next_line(fd);
		db->map_height++;
	}
	ft_map_control(db->map, db);
	complete_to_rect(db->map, db);
}

/*
	This function is used to process the map file. It opens the file.
	Then it reads the file line by line and checks if the file is valid.
	If the map style is not valid, it will throw an error.
*/
void	ft_map_process(t_dB *db, char *argv)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		ft_error("File could not found!\n", db);
	db->line = get_next_line(fd);
	if (!db->line)
		ft_error("Map format is invalid!\n", db);
	while (db->line)
	{
		ft_map_translate(db, db->line, fd);
		if (!db->line)
			break ;
		free(db->line);
		db->line = get_next_line(fd);
	}
	close(fd);
	if (db->map == NULL)
		ft_error("Given map rules are not valid!\n", db);
}
