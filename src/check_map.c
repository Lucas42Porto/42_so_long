/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:45:49 by lumarque          #+#    #+#             */
/*   Updated: 2023/10/03 18:24:16 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	check_format(t_map *map)
{
	int	i;
	size_t	row_len;

	i = -1;
	row_len = ft_strlen(map->tiles[0]);
	while (++i < map->pos.y)
	{
		if (ft_strlen(map->tiles[i]) != row_len)
			return (false);
	}
	map->pos.x = (int)row_len;
	return (true);
}

bool	check_walls(t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->pos.y)
		if (map->tiles[i][0] != WALL || map->tiles[i][map->pos.x - 1] != WALL)
			return (false);
	i = -1;
	while (++i < map->pos.x)
		if (map->tiles[0][i] != WALL || map->tiles[map->pos.y - 1][i] != WALL)
			return (false);
	return (true);
}

int	check_tiles(t_game *game, t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->pos.y)
	{
		j = -1;
		while (++j < map->pos.x)
		{
			if (map->tiles[i][j] == PLAYER)
			{
				map->player++;
				game->curr = (t_point){j, i};
				game->next = game->curr;
			}
			else if (map->tiles[i][j] == EXIT)
				map->exit++;
			else if (map->tiles[i][j] == COIN)
				map->coins++;
			else if (!ft_strchr(TILES, map->tiles[i][j]))
				return (0);
		}
	}
	return (map->player == 1 && map->exit == 1 && map->coins >= 1);
}

int	check_paths(t_game *game, t_map *map)
{
	int	i;
	int		reach_exit;
	char	**tiles;

	i = -1;
	reach_exit = 0;
	tiles = ft_calloc(map->pos.y + 1, sizeof(char *));
	if (!tiles)
		exit_error(game, "Malloc failed.");
	while (++i < map->pos.y)
	{
		tiles[i] = ft_strdup(map->tiles[i]);
		{
			if (!tiles[i])
			{
				clean_tiles(tiles);
				exit_error(game, "Malloc failed.");
			}
		}
	}
	reach_exit = flood_fill(map, game->curr, tiles);
	clean_tiles(tiles);
	return (reach_exit);
}

void	check_map(t_game *game)
{
	if (!game->map->pos.y)
		exit_error(game, "Map is empty.");
	if (!check_format(game->map))
		exit_error(game, "Map is not a rectangle.");
	if (!check_walls(game->map))
		exit_error(game, "Map is not surrounded by walls.");
	if (!check_tiles(game, game->map))
		exit_error(game, "Map has invalid tiles.");
	if (!check_paths(game, game->map))
		exit_error(game, "Map has invalid path.");
}