/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 19:17:47 by lumarque          #+#    #+#             */
/*   Updated: 2023/09/23 16:02:43 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>

void	init_game(char *file)
{
	t_game	game;
	
	ft_bzero(&game, sizeof(t_game));
	read_map(&game, file);
	check_map(&game);
	launch_mlx(&game, game.map);
	load_img(&game);
	render_map(&game, game.map);
	mlx_hook(game.win_ptr, ON_KEYPRESS, KEYPRESS_MASK, handle_keypress, &game);
	mlx_hook(game.win_ptr, ON_CLOSE, CLOSE_MASK, endgame, &game);
	mlx_loop_hook(game.mlx_ptr, render_move, &game);
	mlx_loop(game.mlx_ptr);
}

int	main(int ac, char **av)
{
	if (ac != 2)
		exit_error(NULL, "Invalid number of arguments.");
	check_filename(av[1]);
	init_game(av[1]);
}
