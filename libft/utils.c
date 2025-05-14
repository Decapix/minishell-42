/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42,fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:40:33 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/14 08:01:29 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nb, size_t size)
{
	size_t	i;
	void	*buffer;

	if (nb * size > 2147483647)
		return (0);
	i = 0;
	buffer = malloc(nb * size);
	if (!buffer)
		return (0);
	while (i < nb * size)
		((char *)buffer)[i++] = (char)0;
	return (buffer);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strdup(char *str)
{
	char	*buffer;
	int		i;

	buffer = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!buffer)
		return (0);
	i = 0;
	while (str[i])
	{
		buffer[i] = str[i];
		i++;
	}
	return (buffer);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}
