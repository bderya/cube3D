/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 20:13:53 by yogun             #+#    #+#             */
/*   Updated: 2022/12/11 22:03:17 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char *argv[]) {
	t_dB	data;

	if (argc == 2)
	{
		if (!is_map_format_ok(argv[1], ".cub"))
			error_print("Wrong map format!\n");
		parse_map(&data, argv[1]);
		//play_game();
	}
	else
		ft_putstr_fd("Error!\nInvalid input!\n", 2);
	return (1);

//   void *mlx = mlx_init();
//   void *window = mlx_new_window(mlx, WIDTH, HEIGHT, "Wolfenstein 3D");
//   int *map = argv[1]; // Assumes that the map array is passed as the first argument

//   Player player = {0, 0, 0, 60}; // Initialize the player at the origin facing right

//   while (1) {
//     // Handle keyboard input
//     int key = mlx_get_key(mlx, window);
//     if (key == 'w') {
//       player.x += cos(player.direction) * 0.1;
//       player.y += sin(player.direction) * 0.1;
//     } else if (key == 's') {
//       player.x -= cos(player.direction) * 0.1;
//       player.y -= sin(player.direction) * 0.1;
//     } else if (key == 'a') {
//       player.direction -= 0.1;
//     } else if (key == 'd') {
//       player.direction += 0.1;
//     }

//     // Handle mouse input
//     int mouse_x, mouse_y;
//     mlx_get_mouse_pos(mlx, window, &mouse_x, &mouse_y);
//     player.direction = (mouse_x / (double)WIDTH) * player.fov - (player.fov / 2);

//     // Clear the screen
//     mlx_clear_window(mlx, window);

//     // Draw the live map view
//     mlx_string_put(mlx, window, 10, 10, 0xffffff, "Live map view");

//     // Cast rays to find the distance to walls
//     for (int x = 0; x < WIDTH; x++) {
//       // Calculate the angle of the ray
//       double angle = player.direction - player.fov / 2 + (x / (double)WIDTH) * player.fov;

//       // Find the distance to the wall in the direction of the ray
//       double distance = 0;
//       while (map[(int)player.x + distance * cos(angle)][(int)player.y + distance * sin(angle)] == 0) {
//         distance += 0.01;
//       }

//       // Draw a vertical line representing the wall
//       int line_height = (HEIGHT / distance) * 3;
//       mlx_line(mlx, window, x, HEIGHT / 2 - line_height / 2, x, HEIGHT / 2 + line_height / 2, 0xffffff);
//     }

//     // Update the screen
//     mlx_loop(mlx);

  //return 1;
}