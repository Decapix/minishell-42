/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:33:11 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/19 13:43:23 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_envsize(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next_var;
		i++;
	}
	return (i);
}

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*res;

	res = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!res)
		return (0);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	return (res);
}

int	sig_ctr(pid_t *child_id, int total_child)
{
	int		i;
	int		tmp;		
	pid_t	result;
	int		status;

	tmp = total_child;
	result = 0;
	while (total_child > 0)
	{
		i = 0;
		while (i < tmp)
		{
			if (i == tmp - 1 && child_id[i])
				result = waitpid(child_id[i], &status, WNOHANG);
			else if (child_id[i])
				result = waitpid(child_id[i], 0, WNOHANG);
			if (result)
				child_id[i] = decrement_return_z(&total_child);
			if (g_status == 2)
				paint_in_red(child_id, tmp);
			i++;
		}
	}
	return (sync_status(status));
}

int	update_path(t_shell *command, char **path)
{
	char	*buffer;
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strjoin("/", command->command->str);
	if (!tmp)
		return (-1);
	while (path[i])
	{
		buffer = ft_strjoin(path[i++], tmp);
		if (!buffer)
			return (-1);
		if (!access(buffer, F_OK | X_OK))
		{
			free(command->command->str);
			free(tmp);
			command->command->str = buffer;
			return (0);
		}
		else
			free(buffer);
	}
	free(tmp);
	return (1);
}

void	close_remaining_fds(int fd[4])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (fd[i] > 2)
			close(fd[i]);
		i++;
	}
}
