/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endgame.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:17:09 by lumarque          #+#    #+#             */
/*   Updated: 2023/09/23 15:07:31 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	destroy_image(t_game *game)
{
	if(!game->floor.ptr)
		return ;
	mlx_destroy_image(game->mlx_ptr, game->wall.ptr);
	mlx_destroy_image(game->mlx_ptr, game->floor.ptr);
	mlx_destroy_image(game->mlx_ptr, game->exit.ptr);
	mlx_destroy_image(game->mlx_ptr, game->collect.ptr);
	mlx_destroy_image(game->mlx_ptr, game->character.ptr);
	mlx_destroy_image(game->mlx_ptr, game->character_l.ptr);
	mlx_destroy_image(game->mlx_ptr, game->character_r.ptr);
	mlx_destroy_image(game->mlx_ptr, game->character_u.ptr);
}

void	clean_tiles(char **tiles)
{
	size_t	i;

	i = 0;
	if (!tiles)
		return ;
	while (tiles[i])
		free (tiles[i++]);
	free (tiles);
}

void	clean_map(t_map *map)
{
	if (!map)
		return ;
	clean_tiles(map->tiles);
	free (map);
}

void	clean_game(t_game *game)
{
	if (!game)
		return ;
	if (game->map)
		clean_map(game->map);
	destroy_image(game);

	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
		mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
}

int	endgame(t_game *game)
{
	clean_game(game);
	ft_putstr_fd("End Game !\n", 2);
	exit(EXIT_SUCCESS);
}
