/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 21:47:03 by yogun             #+#    #+#             */
/*   Updated: 2022/12/12 16:32:07 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUBE3D_H
# define CUBE3D_H

# define WIDTH 640
# define HEIGHT 480

# include "libft/libft.h"
# include "mlx/mlx.h"
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>


typedef struct s_dB {
	char	*line;
	t_list	*map;
	void	*no;
	void	*so;
	void	*ea;
	void	*we;
	int		c[3];
	int		f[3];
	double	map_width;
	double	map_height;
	char	player;
	double	px;
	double	py;
}				t_dB;

void	error_print(char *s, t_dB *data);
int		is_map_format_ok(char *str, char *str2);
void	ft_map_process(t_dB *data, char *argv);
void	ft_check_parameters(t_dB *data, char *line, int fd);
void	texture_check(t_dB *data, char *line, char c);
void	color_check(t_dB *data, char *line, char c);
int		color_check_2(char *line, int i, t_dB *data);

#endif