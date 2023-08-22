/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antferna <antferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:22:37 by antferna          #+#    #+#             */
/*   Updated: 2023/07/14 13:48:38 by antferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	allocate_map(char *line, t_game *game, int fd, char *map_name);
static int	allocate_map2(char *line, t_game *game, int fd, char *map_name);

void	free_maps(t_game *g)
{
	char	**map_area_start;
	char	**map_cpy_start;

	if (!g->map && !g->map_cpy)
		return ;
	map_area_start = g->map;
	map_cpy_start = g->map_cpy;
	while (*(g->map))
	{
		free(*(g->map));
		g->map++;
	}
	free(map_area_start);
	while (*(g->map_cpy))
	{
		free(*(g->map_cpy));
		g->map_cpy++;
	}
	free(map_cpy_start);
}

static void	free_map(t_game *game, int i)
{
	int	j;

	j = i;
	if (game->map)
	{
		if (game->map[i] != NULL)
			free(game->map[i]);
		while (--i >= 0)
			free(game->map[i]);
		free(game->map);
	}
	if (game->map_cpy)
	{
		if (game->map_cpy[i] != NULL)
			free(game->map_cpy[i]);
		while (--j >= 0)
			free(game->map_cpy[j]);
		free(game->map_cpy);
	}
}

int	read_map(char *map_name, t_game *game)
{
	int		fd;
	char	*line;

	line = NULL;
	if (check_extension(map_name) == FALSE)
		return (FALSE);
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error: No se encontro el fichero o no se pudo abrir.\n");
		return (FALSE);
	}
	if (allocate_map(line, game, fd, map_name) == FALSE)
		return (FALSE);
	return (TRUE);
}

static int	allocate_map(char *line, t_game *game, int fd, char *map_name)
{
	line = get_next_line(fd);
	if (line == NULL)
	{
		ft_printf("Error: Mapa vacío.\n");
		return (FALSE);
	}
	while (line != NULL)
	{
		game->row++;
		free(line);
		line = get_next_line(fd);
	}
	game->map = ft_calloc(game->row + 1, sizeof(char *));
	game->map_cpy = ft_calloc(game->row +1, sizeof(char *));
	if (!game->map || !game->map_cpy)
		return (free(line), FALSE);
	close(fd);
	if (allocate_map2(line, game, fd, map_name) == FALSE)
		return (free(line), FALSE);
	return (free(line), TRUE);
}

static int	allocate_map2(char *line, t_game *game, int fd, char *map_name)
{
	int	i;

	i = 0;
	fd = open(map_name, O_RDONLY);
	line = get_next_line(fd);
	game->lenlines = (ft_strlen(line) - 1);
	while (line != NULL)
	{
		game->col = ft_strlen(line);
		game->map[i] = ft_calloc(game->col, sizeof(char));
		game->map_cpy[i] = ft_calloc(game->col, sizeof(char));
		if (!game->map[i] && !game->map_cpy[i])
			return (free_map(game, i), free(line), FALSE);
		ft_strlcpy(game->map[i], line, ft_strlen(line)
			+ (line[ft_strlen(line) - 1] != '\n'));
		ft_strlcpy(game->map_cpy[i], line, ft_strlen(line)
			+ (line[ft_strlen(line) - 1] != '\n'));
		free(line);
		line = get_next_line(fd);
		i++;
	}
	game->map[i] = NULL;
	game->map_cpy[i] = NULL;
	close(fd);
	return (free(line), TRUE);
}
