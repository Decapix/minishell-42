/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesicstudent.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:05:41 by apesic            #+#    #+#             */
/*   Updated: 2025/05/17 18:05:44 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

char	*join_var_equals_value(const char *var, const char *val)
{
	size_t	len_var;
	size_t	len_val;
	char	*res;
	size_t	i;
	size_t	j;

	len_var = 0;
	len_val = 0;
	i = 0;
	j = 0;
	while (var[len_var])
		len_var++;
	while (val[len_val])
		len_val++;
	res = malloc(len_var + 1 + len_val + 1);
	if (!res)
		return (NULL);
	while (i < len_var)
		res[i] = var[i++];
	res[i++] = '=';
	while (j < len_val)
		res[i++] = val[j++];
	res[i] = '\0';
	return (res);
}

t_list	*ft_lstnew(char *str)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->str = str;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_back(t_list **lst, t_list *neww)
{
	t_list	*last;

	if (!lst || !neww)
		return ;
	if (*lst == NULL)
	{
		*lst = neww;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = neww;
}

void	ft_lstclear(t_list **lst)
{
	t_list	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->str);
		free(*lst);
		*lst = tmp;
	}
}
