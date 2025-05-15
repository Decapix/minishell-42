/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42,fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:32:10 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/15 13:49:17 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <stdlib.h>
# include "../struct.h"

void	exit_program(t_env *mini_env, int error_code);
int		print_error(int error_code);

int		ft_strlen(char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_putstr_fd(char *str, int fd);
void	*ft_calloc(size_t nb, size_t size);

int		init_prompt_structure(t_env *mini_env, char *str);
int		how_many_commands(char *str);

int		ft_istoken(char c);
int		ft_isspace(char c);
int		ft_isalpha(char c);
int		ft_isquote(char c);
int		ft_isprint(char c);
int		check_the_char(t_env *mini_env, t_shell **command, char *str, int i);

void	write_and_jump_quotes(char *buffer, char *str, int i);
t_io	*init_new_io(t_env *mini_env, t_shell *command, int input);

int		give_input(t_env *mini_env, t_shell *command, char *str, int i);
int		give_output(t_env *mini_env, t_shell *command, char *str, int i);
int		give_name(t_env *mini_env, char **to_store, char *str, int i);
int		give_command_name(t_env *mini_env, t_shell *comand, char *str, int i);
int		give_pipe(t_env *mini_env, t_shell **command, int i);

#endif
