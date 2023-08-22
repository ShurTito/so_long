/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antferna <antferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 14:57:04 by antferna          #+#    #+#             */
/*   Updated: 2023/07/14 14:34:39 by antferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize_s_game(t_game *game)
{
	game->col = 0;
	game->row = 0;
	game->lenlines = 0;
	game->items = 0;
	game->e = 0;
	game->p = 0;
	game->items_cpy = 0;
	game->e_cpy = 0;
	game->moves = 0;
}

static int	init_imgs(t_game *game)
{
	game->text_exit1 = mlx_load_png("./images/chest.png");
	game->text_exit2 = mlx_load_png("./images/chest2.png");
	game->text_floor = mlx_load_png("./images/floor.png");
	game->text_item = mlx_load_png("./images/key.png");
	game->text_pdown = mlx_load_png("./images/playerdown.png");
	game->text_pleft = mlx_load_png("./images/playerleft.png");
	game->text_pright = mlx_load_png("./images/playerright.png");
	game->text_pup = mlx_load_png("./images/playerup.png");
	game->text_wall = mlx_load_png("./images/wall.png");
	game->img_exit1 = mlx_texture_to_image(game->mlx, game->text_exit1);
	game->img_exit2 = mlx_texture_to_image(game->mlx, game->text_exit2);
	game->img_floor = mlx_texture_to_image(game->mlx, game->text_floor);
	game->img_item = mlx_texture_to_image(game->mlx, game->text_item);
	game->img_pdown = mlx_texture_to_image(game->mlx, game->text_pdown);
	game->img_pleft = mlx_texture_to_image(game->mlx, game->text_pleft);
	game->img_pright = mlx_texture_to_image(game->mlx, game->text_pright);
	game->img_pup = mlx_texture_to_image(game->mlx, game->text_pup);
	game->img_wall = mlx_texture_to_image(game->mlx, game->text_wall);
	clean_textures(game);
	if (img_error(game) == FALSE)
		return (FALSE);
	return (TRUE);
}

void	close_game(void *param)
{
	t_game	*game;

	game = param;
	free_maps(game);
	mlx_close_window(game->mlx);
}

static int	main2(t_game *game)
{
	if (init_imgs(game) == FALSE)
		return (free(game), FALSE);
	if (image_to_window(game) == FALSE)
		return (free(game), FALSE);
	mlx_key_hook(game->mlx, &p_move, game);
	mlx_close_hook(game->mlx, &close_game, game);
	return (TRUE);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		return (ft_printf("Error: Introduzca un mapa./n"), EXIT_FAILURE);
	game = malloc(sizeof(t_game));
	if (!game)
		return (EXIT_FAILURE);
	initialize_s_game(game);
	if (read_map(argv[1], game) == FALSE)
		return (free(game), EXIT_FAILURE);
	if (check_map(game) == FALSE)
		return (free_maps(game), free(game), EXIT_FAILURE);
	game->mlx = mlx_init(IMG_W * game->col, IMG_H * game->row, "SO_LONG", true);
	if (!game->mlx)
		return (free(game), EXIT_FAILURE);
	if (main2(game) == FALSE)
		return (free(game), EXIT_FAILURE);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (free(game), EXIT_SUCCESS);
}
