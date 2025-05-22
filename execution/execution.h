/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:37:00 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/21 16:40:32 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../struct.h"
# include "../libft/libft.h"
# include "../env_mini/env_mini.h"
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>

void	*ft_calloc(size_t nb, size_t size);
int		print_error(int error_code);
void	free_double_char(char **arr);
void	exit_program(t_env *mini_env, int error_code);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

int		close_and_zero(int fd);
int		decrement_return_z(int *to_decrement);
void	make_it_zero(int fd[4]);

int		ft_exit(t_env *mini_env, t_leak *garbage, t_shell *cmd);
int		ft_env(t_env *mini_env);
int		ft_echo(char **str);
int		ft_pwd(void);
int		ft_export(t_env *mini_env, t_shell *command);
int		ft_unset(t_env *mini_env, t_shell *command);
int		ft_cd(t_env *mini_env, t_shell *command);

char	*ft_strjoin(char *s1, char *s2);
int		ft_envsize(t_env *lst);
int		ft_lstsize(t_list *lst);

char	*get_next_line(int fd);

char	**t_env_to_arr(t_env *mini_env);
void	execute_command(t_env *mini_env, t_shell *command, char **path);
int		update_path(t_shell *command, char **path);
int		exec_com(t_env *env, t_shell *command, int fd[4], t_leak *garbage);

t_leak	*nice_little_trash(t_env *mini_env, char **path, t_shell *command);
int		clean_garbage(t_leak *garbage);
int		error_child(t_env *mini_env, t_list *lst, t_leak *garbage);

int		is_special_buildin(t_env *mini_env, t_shell *command, t_leak *garbage);
int		ft_isbuildin(char *str);
void	execute_buildin(t_env *mini_env, t_leak *gar, char **arg, t_shell *cmd);

int		set_input(t_env *mini_env, t_io	*input, int fd[4]);
void	set_output(t_io *output, int fd[4]);
int		init_exec(t_env *mini_env, t_shell **command, int fd[4], char **path);

pid_t	*init_pid_array(t_env *mini_env, int nb_of_command);
int		size_t_shell(t_shell *command);
int		sig_ctr(pid_t *child_id, int nb_of_commands);
int		sync_status(int status);
void	paint_in_red(pid_t *child_id, int total_child);

#endif
