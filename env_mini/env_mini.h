/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mini.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:22:54 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/16 12:12:05 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_MINI_H
# define ENV_MINI_H

# include "../struct.h"
# include "stdlib.h"

void	*ft_calloc(size_t nb, size_t size);
void	exit_program(t_env *mini_env, int error_code);
char	*ft_strdup(char *str);

void	extract_env(t_env *mini_env, char **envp);

char	**extract_path(char *full_path);
void	give_simple_path(t_env *mini_env);
char	*copy_from_i_to_j(int *i, int j, char *full_path);
int		search_for_var(char **envp, char *var, int len);

int		ft_strcopy(char *s1, char *s2);
int		ft_strlen(char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isspace(char c);
int		ft_isquote(char c);

t_env	*set_up_env(char **envp);
void	replace_dollar(t_env *mini_env, t_shell *command);

#endif
