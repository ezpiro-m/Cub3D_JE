/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjesberg <jjesberg@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 00:22:12 by jjesberg          #+#    #+#             */
/*   Updated: 2023/01/04 22:04:44 by jjesberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static int	check(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]) && s[i] != '\n' && !(s[i] <= 32))
			return (COLOUR_ERROR);
		i++;
	}
	return (0);
}

int	save_colours(char *s, t_data *data)
{
	int	*ptr1;
	int	ret;
	int	i;
	int	j;

	ret = 0;
	j = 0;
	i = 1;
	if (s[0] == 'C')
		ptr1 = data->C;
	if (s[0] == 'F')
		ptr1 = data->F;
	while (j < 3)
	{
		if (sp_dg_skipper(s, &i) == COLOUR_ERROR)
			ret = COLOUR_ERROR;
		if (j == 2)
		{
			if (check(s + i) == COLOUR_ERROR)
				return (COLOUR_ERROR);
		}
		ptr1[j++] = ft_atoi(s + i);
	}
	return (ret);
}

int	find_map(char *map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] != '\0')
	{
		if (map[i] == '1' && !ft_haschar(map, 'F') && \
		!ft_haschar(map, 'C') && !ft_haschar(map, 'W') \
		&& !ft_haschar(map, 'A') && !ft_haschar(map, 'O'))
		{
			j = i + 1;
			while (map[j] == '1')
				j++;
			if (j - i >= 3)
				return (i);
		}
		i++;
	}
	return (-1);
}