/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antferna <antferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:54:36 by antferna          #+#    #+#             */
/*   Updated: 2023/07/13 16:17:08 by antferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

# define IMG_W 48
# define IMG_H 48
# define IS 48
# define TRUE 1
# define FALSE 0

typedef struct s_point
{
	int		x;
	int		y;
}			t_point;

typedef struct s_game
{
	mlx_t			*mlx;
	char			**map;
	char			**map_cpy;
	int				col;
	size_t			lenlines;
	int				row;
	t_point			player;
	t_point			box;
	int				items;
	int				p;
	int				e;
	int				items_cpy;
	int				e_cpy;
	int				moves;
	mlx_texture_t	*text_pdown;
	mlx_image_t		*img_pdown;
	mlx_texture_t	*text_pup;
	mlx_image_t		*img_pup;
	mlx_texture_t	*text_pleft;
	mlx_image_t		*img_pleft;
	mlx_texture_t	*text_pright;
	mlx_image_t		*img_pright;
	mlx_texture_t	*text_floor;
	mlx_image_t		*img_floor;
	mlx_texture_t	*text_wall;
	mlx_image_t		*img_wall;
	mlx_texture_t	*text_item;
	mlx_image_t		*img_item;
	mlx_texture_t	*text_exit1;
	mlx_image_t		*img_exit1;
	mlx_texture_t	*text_exit2;
	mlx_image_t		*img_exit2;

}			t_game;

int			read_map(char *map_name, t_game *game);
int			check_map(t_game *game);
int			check_extension(char *map_name);
int			image_to_window(t_game *game);
void		p_move(mlx_key_data_t keydata, void *param);
void		free_maps(t_game *g);
void		clean_textures(t_game *g);
int			img_error(t_game *g);
void		close_game(void *param);

#endif