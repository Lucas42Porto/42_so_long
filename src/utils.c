/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:27:04 by lumarque          #+#    #+#             */
/*   Updated: 2023/09/23 15:55:17 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	exit_error(t_game *game, char *msg)
{
	clean_game(game);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit (EXIT_FAILURE);
}

void	check_filename(char *file)
{
	size_t	i;

	i = ft_strlen(file);
	if (i <= 4)
		exit_error(NULL, "Invalid file name.");
	else if (!ft_strnstr((file + i - 4), ".ber", 4))
		exit_error(NULL, "Invalid file extension.");
}

t_tile	get_tile(t_game *so_long, t_point p)
{
	return (so_long->map->tiles[p.y][p.x]);
}

int	is_same_point(t_point a, t_point b)
{
	return (a.x == b.x && a.y == b.y);
}

int	flood_fill(t_map *map, t_point curr, char **path)
{
	static int	coins = 0;
	static int	exit = 0;

	if (path[curr.y][curr.x] == WALL)
		return (0);
	else if (path[curr.y][curr.x] == COIN)
		coins++;
	else if (path[curr.y][curr.x] == EXIT)
		exit = 1;
	path[curr.y][curr.x] = WALL;
	flood_fill(map, (t_point){curr.x + 1, curr.y}, path);
	flood_fill(map, (t_point){curr.x - 1, curr.y}, path);
	flood_fill(map, (t_point){curr.x, curr.y + 1}, path);
	flood_fill(map, (t_point){curr.x, curr.y - 1}, path);
	return (coins == map->coins && exit == 1);
}
