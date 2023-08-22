/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antferna <antferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 12:20:48 by antferna          #+#    #+#             */
/*   Updated: 2023/07/13 16:17:00 by antferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	img_error(t_game *game)
{
	if (!game->img_exit1 || !game->img_exit2 || !game->img_floor
		|| !game->img_item || !game->img_pdown || !game->img_pleft
		|| !game->img_pright || !game->img_pup || !game->img_wall
		|| !game->text_exit1 || !game->text_exit2 || !game->text_floor
		|| !game->text_item || !game->text_pdown || !game->text_pleft
		|| !game->text_pright || !game->text_pup || !game->text_wall)
		return (FALSE);
	return (TRUE);
}

void	clean_textures(t_game *g)
{
	mlx_delete_texture(g->text_exit1);
	mlx_delete_texture(g->text_exit2);
	mlx_delete_texture(g->text_floor);
	mlx_delete_texture(g->text_item);
	mlx_delete_texture(g->text_pdown);
	mlx_delete_texture(g->text_pleft);
	mlx_delete_texture(g->text_pright);
	mlx_delete_texture(g->text_pup);
	mlx_delete_texture(g->text_wall);
}

static int	image_to_window_3(t_game *game, int i, int j)
{
	if (game->map[i][j] == 'C')
	{
		if (mlx_image_to_window(game->mlx, game->img_floor, j * IS, i * IS) < 0)
			return (FALSE);
		if (mlx_image_to_window(game->mlx, game->img_item, j * IS, i * IS) < 0)
			return (FALSE);
	}
	if (game->map[i][j] == 'P')
	{
		if (mlx_image_to_window(game->mlx, game->img_floor, j * IS, i * IS) < 0)
			return (FALSE);
		if (mlx_image_to_window(game->mlx, game->img_pdown, j * IS, i * IS) < 0)
			return (FALSE);
	}
	return (TRUE);
}

static int	image_to_window_2(t_game *game, int i, int j)
{
	if (game->map[i][j] == '1')
		if (mlx_image_to_window(game->mlx, game->img_wall, j * IS, i * IS) < 0)
			return (FALSE);
	if (game->map[i][j] == '0')
		if (mlx_image_to_window(game->mlx, game->img_floor, j * IS, i * IS) < 0)
			return (FALSE);
	if (game->map[i][j] == 'E')
	{
		if (mlx_image_to_window(game->mlx, game->img_floor, j * IS, i * IS) < 0)
			return (FALSE);
		if (mlx_image_to_window(game->mlx, game->img_exit1, j * IS, i * IS) < 0)
			return (FALSE);
	}
	return (TRUE);
}

int	image_to_window(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->row)
	{
		j = -1;
		while (++j < game->col)
		{
			if (image_to_window_2(game, i, j) == FALSE)
				return (FALSE);
			if (image_to_window_3(game, i, j) == FALSE)
				return (FALSE);
		}
	}
	return (TRUE);
}
