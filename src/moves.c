/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:45:21 by lumarque          #+#    #+#             */
/*   Updated: 2023/11/29 20:10:34 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_keypress(int keysym, t_game *game)
{
	if (keysym == UP || keysym == W)
		game->next = (t_point){game->curr.x, game->curr.y - 1};
	if (keysym == DOWN || keysym == S)
		game->next = (t_point){game->curr.x, game->curr.y + 1};
	if (keysym == LEFT || keysym == A)
		game->next = (t_point){game->curr.x - 1, game->curr.y};
	if (keysym == RIGHT || keysym == D)
		game->next = (t_point){game->curr.x + 1, game->curr.y};
	if (keysym == ESC)
		endgame(game);
	return (0);
}

int	check_move(t_game *game)
{
	return (!is_same_point(game->curr, game->next) \
		&& get_tile(game, game->next) != WALL);
}

void	move_player(t_game *game, t_map *map)
{
	static t_tile	previous = SPACE;

	map->tiles[game->curr.y][game->curr.x] = previous;
	if (get_tile(game, game->next) != COIN)
		previous = map->tiles[game->next.y][game->next.x];
	else
		previous = SPACE;
	map->tiles[game->next.y][game->next.x] = PLAYER;
	render_tile(game, (t_point){game->curr.x, game->curr.y});
	render_tile(game, (t_point){game->next.x, game->next.y});
	game->curr = game->next;
}

int	render_move(t_game *game)
{
	if (!check_move(game))
		return (0);
	ft_putstr_fd("Moves: ", 1);
	ft_putnbr_fd(++game->moves, 1);
	ft_putstr_fd("\n", 1);
	if (get_tile(game, game->next) == COIN)
		game->coin++;
	else if (get_tile(game, game->next) == EXIT \
		&& game->coin == game->map->coins)
		endgame(game);
	move_player(game, game->map);
	return (0);
}
