/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42,fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:51:31 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/21 16:15:39 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "../libft/libft.h"
# include "../struct.h"
# include <stdlib.h>
# include <unistd.h>

void	*ft_calloc(size_t nb, size_t size);
int		ft_strlen(char *str);
void	exit_program(t_env *mini_env, int error_code);
void	free_double_char(char **to_free);
int		clean_garbage(t_leak *garbage);

void	ft_lstclear(t_list **lst);
void	ft_lstadd_back(t_list **lst, t_list *neww);
t_list	*ft_lstnew(char *str);
char	*join_var_equals_value(char *var, char *val);

int		ft_exit(t_env *mini_env, t_leak *garbage, t_shell *cmd);
int		ft_env(t_env *mini_env);
int		ft_echo(char **str);
int		ft_pwd(void);
int		ft_export(t_env *mini_env, t_shell *command);
int		ft_unset(t_env *mini_env, t_shell *command);
int		ft_cd(t_env *mini_env, t_shell *command);
bool	valid_export(t_shell *command);
void	add_var_name(t_env *begin, t_env *mini_env, char *var, int *i);
void	add_var_content(t_env *begin, t_env *mini_env, char *var, int i);

#endif
