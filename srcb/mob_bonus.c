/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mob_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antferna <antferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:40:51 by antferna          #+#    #+#             */
/*   Updated: 2023/07/14 14:33:39 by antferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	mob_sprite(t_game *g)
{
	int	i;
	int	j;

	i = -1;
	while (g->map[++i])
	{
		j = -1;
		while (g->map[i][++j])
		{
			if (g->map[i][j] == 'M')
			{
				mlx_image_to_window(g->mlx, g->img_floor, j * IS, i * IS);
				mlx_image_to_window(g->mlx, g->img_mob2, j * IS, i * IS);
			}
		}
	}
	g->mob_move = 1;
}

void	mob_sprite2(t_game *g)
{
	int	i;
	int	j;

	i = -1;
	while (g->map[++i])
	{
		j = -1;
		while (g->map[i][++j])
		{
			if (g->map[i][j] == 'M')
			{
				mlx_image_to_window(g->mlx, g->img_floor, j * IS, i * IS);
				mlx_image_to_window(g->mlx, g->img_mob1, j * IS, i * IS);
			}
		}
	}
	g->mob_move = 0;
}

void	put_counter(t_game *g)
{
	char	*counter;

	counter = ft_itoa(g->moves);
	mlx_image_to_window(g->mlx, g->img_wall, 0, 0);
	mlx_put_string(g->mlx, counter, 5, 5);
	free(counter);
}

void	close_game(void *param)
{
	t_game	*game;

	game = param;
	free_maps(game);
	mlx_close_window(game->mlx);
}
