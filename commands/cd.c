/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesicstudent.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 10:34:49 by apesic            #+#    #+#             */
/*   Updated: 2025/05/17 10:34:51 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

static char	*env_get(t_env *mini_env, char *name)
{
	t_env	*cur;
	size_t	len;

	len = ft_strlen(name);
	cur = mini_env;
	while (cur)
	{
		if (ft_strncmp(cur->var_name, name, len) == 0
			&& cur->var_name[len] == '\0')
			return (cur->var);
		cur = cur->next_var;
	}
	return (NULL);
}

static int	call_export(t_env *mini_env, char *var, char *val)
{
	char	*arg;
	t_list	*lst;
	int		ret;
	t_shell	cmd;

	arg = join_var_equals_value(var, val);
	if (!arg)
		return (1);
	lst = ft_lstnew(ft_strdup("export"));
	ft_lstadd_back(&lst, ft_lstnew(arg));
	cmd.command = lst;
	cmd.is_buildin = 1;
	cmd.input = 0;
	cmd.output = 1;
	cmd.first_input = NULL;
	cmd.first_output = NULL;
	cmd.next_command = NULL;
	ret = ft_export(mini_env, &cmd);
	ft_lstclear(&lst);
	return (ret);
}

int	ft_check_and_chdir(t_env *env, char *target, char *cwd)
{
	struct stat	sb;

	if (stat(target, &sb) != 0)
		return (perror("cd"), 1);
	if (!S_ISDIR(sb.st_mode))
	{
		write(2, "cd: not a directory: ", 22);
		write(2, target, ft_strlen(target));
		write(2, "\n", 1);
		return (1);
	}
	if (!getcwd(cwd, PATH_MAX))
		return (perror("getcwd"), 1);
	if (chdir(target) != 0)
		return (perror("cd"), 1);
	if (call_export(env, "OLDPWD", cwd) != 0)
		return (1);
	if (!getcwd(cwd, PATH_MAX))
		return (perror("getcwd"), 1);
	if (call_export(env, "PWD", cwd) != 0)
		return (1);
	return (0);
}

int	ft_cd(t_env *env, t_shell *cmd)
{
	t_list	*args;
	char	*target;
	char	*home;
	char	cwd[PATH_MAX];

	args = cmd->command;
	if (args && args->next && args->next->str)
		target = args->next->str;
	else
	{
		home = env_get(env, "HOME");
		if (!home)
			return (write(2, "cd: HOME not set\n", 18), 1);
		target = home;
	}
	if (ft_strncmp(target, "-", ft_strlen(target)) == 0)
	{
		target = env_get(env, "OLDPWD");
		if (!target)
			return (write(2, "cd: OLDPWD not set\n", 20), 1);
		printf("%s\n", target);
	}
	return (ft_check_and_chdir(env, target, cwd));
}
