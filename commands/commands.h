/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42,fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:51:31 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/16 14:13:15 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "../struct.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>

void	*ft_calloc(size_t nb, size_t size);
int		ft_strlen(char *str);
void	exit_program(t_env *mini_env, int error_code);
void	free_double_char(char **to_free);

int		ft_exit(t_env *mini_env, char **env);
int		ft_env(t_env *mini_env);
int		ft_echo(char **str);
int		ft_pwd(void);
int		ft_export(t_env *mini_env, t_shell *command);
int		ft_unset(t_env *mini_env, t_shell *command);
int     ft_cd(t_env *mini_env, t_shell *command);

#endif
