/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <marvin@42.f>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:27:10 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/05 11:33:28 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

char	*ft_strnjoin(char const *s1, char const *s2, int n)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	while (s1[i])
		i++;
	j = 0;
	while (s2[j])
		j++;
	res = (char *)ft_calloc((i + j + 1), sizeof(char));
	if (!res)
		return (0);
	i = 0;
	j = 0;
	while (s1[j])
		res[i++] = s1[j++];
	j = 0;
	while (s2[j] && j < n)
		res[i++] = s2[j++];
	return (res);
}

char	*copy_and_delete(char *s1, char *s2, int i)
{
	int	j;

	j = 0;
	while (s2[i])
	{
		s1[j++] = s2[i];
		s2[i++] = '\0';
	}
	while (j < BUFFER_SIZE)
		s1[j++] = '\0';
	return (s1);
}

char	*read_till_newline(char *res, int fd, char *save)
{
	char	*temp;
	char	*newres;
	int		i;
	int		r;

	i = 0;
	temp = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!temp)
		return (0);
	r = read(fd, temp, BUFFER_SIZE);
	if (r == 0)
		return (res);
	while (temp[i] != '\n' && temp[i] && i < BUFFER_SIZE)
		i++;
	if (i++ < BUFFER_SIZE && temp[i])
		while (temp[i])
			save = copy_and_delete(save, temp, i);
	newres = ft_strnjoin(res, temp, i);
	if (!newres)
		return (0);
	free(res);
	free(temp);
	if (newres[ft_strlen(newres) - 1] != '\n')
		newres = read_till_newline(newres, fd, save);
	return (newres);
}

int	copy_till_newline(char *res, char *save)
{
	int		i;
	char	*temp;

	i = -1;
	temp = (char *)ft_calloc(BUFFER_SIZE, sizeof(char));
	if (!temp)
		return (2);
	while (save[++i] != '\n' && save[i])
		res[i] = save[i];
	res[i] = save[i];
	temp = copy_and_delete(temp, save, ++i);
	save = copy_and_delete(save, temp, 0);
	free(temp);
	if (!save[0] && res[0] != '\n')
		return (0);
	return (1);
}

char	*get_next_line(int fd)
{
	int			status;
	char		*res;
	static char	save[BUFFER_SIZE];

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (0);
	res = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!res)
		return (0);
	status = copy_till_newline(res, save);
	if (status == 1)
		return (res);
	if (status == 2)
		return (res);
	res = read_till_newline(res, fd, save);
	if (!res)
		return (0);
	if (!res[0])
		return (res);
	return (res);
}
