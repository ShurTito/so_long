/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antferna <antferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:34:36 by antferna          #+#    #+#             */
/*   Updated: 2023/07/14 13:48:46 by antferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	keypress(t_game *g, int new_x, int new_y, void *img_p);
static void	move_player_c(t_game *g, int new_x, int new_y, void *img_p);
static void	move_player_e(t_game *g, int new_x, int new_y, void *img_p);
static void	move_player_0(t_game *g, int new_x, int new_y, void *img_p);

void	p_move(mlx_key_data_t keydata, void *param)
{
	t_game	*g;

	g = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		close_game(g);
	if ((keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_S
			|| keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_A)
		&& keydata.action == MLX_PRESS)
	{
		if (g->mob_move == 0)
			mob_sprite(g);
		else
			mob_sprite2(g);
	}
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		keypress(g, g->player.x - 1, g->player.y, g->img_pleft);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		keypress(g, g->player.x + 1, g->player.y, g->img_pright);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		keypress(g, g->player.x, g->player.y + 1, g->img_pdown);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		keypress(g, g->player.x, g->player.y - 1, g->img_pup);
}

static void	keypress(t_game *g, int new_x, int new_y, void *img_p)
{
	if (g->map[new_y][new_x] == 'C')
	{
		move_player_c(g, new_x, new_y, img_p);
		put_counter(g);
	}
	else if (g->map[new_y][new_x] == 'E' && g->items == g->items_cpy)
		close_game(g);
	else if (g->map[new_y][new_x] == 'M')
		close_game(g);
	else if (g->map[new_y][new_x] == 'E')
	{
		move_player_e(g, new_x, new_y, img_p);
		put_counter(g);
	}
	else if (g->map[new_y][new_x] != '1')
	{
		move_player_0(g, new_x, new_y, img_p);
		put_counter(g);
	}
}

static void	move_player_c(t_game *g, int new_x, int new_y, void *img_p)
{
	mlx_image_to_window(g->mlx, g->img_floor, g->player.x * IS, g->player.y
		* IS);
	if (g->map[g->player.y][g->player.x] == 'E')
		mlx_image_to_window(g->mlx, g->img_exit1, g->player.x * IS, g->player.y
			* IS);
	g->player.x = new_x;
	g->player.y = new_y;
	g->map[g->player.y][g->player.x] = '0';
	mlx_image_to_window(g->mlx, g->img_floor, g->player.x * IS, g->player.y
		* IS);
	mlx_image_to_window(g->mlx, img_p, g->player.x * IS, g->player.y * IS);
	g->items++;
	g->moves++;
	if (g->items == g->items_cpy)
		mlx_image_to_window(g->mlx, g->img_exit2, g->box.x * IS, g->box.y * IS);
}

static void	move_player_e(t_game *g, int new_x, int new_y, void *img_p)
{
	mlx_image_to_window(g->mlx, g->img_floor, g->player.x * IS, g->player.y
		* IS);
	g->player.x = new_x;
	g->player.y = new_y;
	mlx_image_to_window(g->mlx, g->img_floor, g->player.x * IS, g->player.y
		* IS);
	mlx_image_to_window(g->mlx, g->img_exit1, g->player.x * IS, g->player.y
		* IS);
	mlx_image_to_window(g->mlx, img_p, g->player.x * IS, g->player.y * IS);
	g->moves++;
}

static void	move_player_0(t_game *g, int new_x, int new_y, void *img_p)
{
	mlx_image_to_window(g->mlx, g->img_floor, g->player.x * IS, g->player.y
		* IS);
	if (g->map[g->player.y][g->player.x] == 'E')
		mlx_image_to_window(g->mlx, g->img_exit1, g->player.x * IS, g->player.y
			* IS);
	g->player.x = new_x;
	g->player.y = new_y;
	mlx_image_to_window(g->mlx, img_p, g->player.x * IS, g->player.y * IS);
	g->moves++;
}
