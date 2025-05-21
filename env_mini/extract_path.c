/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42,fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 21:08:41 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/21 14:10:54 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_mini.h"

int	findsc(char *str, char to_find, int start)
{
	while (str[start])
	{
		if (str[start] == to_find)
			return (start);
		start++;
	}
	return (start);
}

char	*copy_from_i_to_j(int *i, int j, char *full_path)
{
	char	*buffer;
	int		k;

	buffer = ft_calloc(j - *i + 1, sizeof(char));
	if (!buffer)
		return (0);
	k = 0;
	while (*i < j)
		buffer[k++] = full_path[(*i)++];
	return (buffer);
}

int	total_nb_paths(char *full_path)
{
	int	i;
	int	paths;

	i = 0;
	if (!full_path[i])
		return (0);
	paths = 1;
	while (full_path[i])
		if (full_path[i++] == ':')
			paths++;
	return (paths);
}

char	**error_free(char **tofree, int end)
{
	int	i;

	i = 0;
	while (i < end)
		free(tofree[i++]);
	free(tofree);
	return (0);
}

char	**extract_path(char *full_path)
{
	int		i;
	int		k;
	int		nb_paths;
	char	**paths;

	i = 0;
	if (!full_path)
		return (0);
	nb_paths = total_nb_paths(full_path);
	if (!nb_paths)
		return (0);
	paths = ft_calloc(nb_paths + 1, sizeof(char *));
	if (!paths)
		return (0);
	k = 0;
	while (k < nb_paths)
	{
		paths[k] = copy_from_i_to_j(&i, findsc(full_path, ':', i), full_path);
		if (!paths[k++])
			return (error_free(paths, k));
		i++;
	}
	return (paths);
}
