/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesicstudent.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:42:24 by apesic            #+#    #+#             */
/*   Updated: 2025/05/22 13:42:25 by apesic           ###   ########.fr       */
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
