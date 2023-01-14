/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 02:26:29 by jjesberg          #+#    #+#             */
/*   Updated: 2023/01/15 00:45:30 by nlouro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static void	find_map(t_data *data)
{
	int		i;
	int		j;
	int		flag;
	int		len;

	j = 0;
	flag = 0;
	i = 0;
	while (data->raw_data[i] && flag != 1)
	{
		len = ft_strlen(data->raw_data[i]);
		while (data->raw_data[i][j] && check_map(data->raw_data[i]) && len > 2)
		{
			flag = 1;
			if (data->raw_data[i][j] != '1' && data->raw_data[i][j] != ' ' \
			&& data->raw_data[i][j] != 9)
				exit(cub_error(INVALID_MAP));
			j++;
		}
		if (flag == 1)
			data->map = data->raw_data + i;
		j = 0;
		i++;
	}
}

static void	save_param(t_data *data)
{
	int		i;
	int		texture;

	i = 0;
	if (check_text(data->raw_data, data->tmp))
		exit(cub_error(TEX_PATH_ERROR));
	while (data->raw_data[i])
	{
		texture = find_path_type(data->raw_data[i]);
		if (texture != NONE)
			init_texture(data, data->raw_data[i], texture);
		else if (ft_haschar(data->raw_data[i], 'F') \
		|| ft_haschar(data->raw_data[i], 'C'))
			check_colours(data, data->raw_data[i]);
		i++;
	}
	if (data->c_colour == 0 || data->f_colour == 0)
		exit(cub_error(COLOUR_ERROR));
	find_map(data);
}

/*
 * map_data has a representation of the full content of the filename
 */
static void	map_data(char *map_path, t_data *data)
{
	data->raw_data = get_map(map_path);
	save_param(data);
	if (ft_splitlen(data->map) < 3 || validate_mapchars(data->map))
		exit(cub_error(MAP_ERROR));
	player_checks(data);
	wall_check(data);
}

/*
 * initialise empty t_data structure
 * call map_data() to fill t_data
 */
t_data	*init_data(char *map_path)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		exit(cub_error(MALLOC_ERROR));
	data->raw_data = NULL;
	data->map = NULL;
	data->textures[0] = NULL;
	data->textures[1] = NULL;
	data->textures[2] = NULL;
	data->textures[3] = NULL;
	data->tmp[0] = 0;
	data->tmp[1] = 0;
	data->tmp[2] = 0;
	data->tmp[3] = 0;
	data->f_colour = 0;
	data->c_colour = 0;
	map_data(map_path, data);
	return (data);
}
