/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:50:58 by lumarque          #+#    #+#             */
/*   Updated: 2023/11/29 17:33:50 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	launch_mlx(t_game *game, t_map *map)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		exit_error(game, "Failed to initialize mlx.");
	game->win_ptr = mlx_new_window(game->mlx_ptr, \
			map->pos.x * SIZE, map->pos.y * SIZE, "so_long");
	if (!game->mlx_ptr)
		exit_error(game, "Failed to create window.");
}

void	load_img(t_game *game)
{
	game->wall = new_sprite(game->mlx_ptr, WALL_PATH);
	game->floor = new_sprite(game->mlx_ptr, FLOOR_PATH);
	game->collect = new_sprite(game->mlx_ptr, COLLECT_PATH);
	game->exit = new_sprite(game->mlx_ptr, EXIT_PATH);
	game->character = new_sprite(game->mlx_ptr, CHAR_PATH);
	game->character_l = new_sprite(game->mlx_ptr, CHAR_L_PATH);
	game->character_r = new_sprite(game->mlx_ptr, CHAR_R_PATH);
	game->character_u = new_sprite(game->mlx_ptr, CHAR_U_PATH);
}

t_img	new_sprite(void *mlx, char *path)
{
	t_img	img;

	img.ptr = mlx_xpm_file_to_image(mlx, path, &img.x, &img.y);
	return (img);
}
