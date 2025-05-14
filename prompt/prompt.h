/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42,fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:55:45 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/14 07:55:47 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# ifndef _POSIX_C_SOURCE
#  define _POSIX_C_SOURCE 1
# endif

# include "../struct.h"
# include <signal.h>
# include <stdio.h>
# include <strings.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <termios.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

char	*ft_strjoin(char *s1, char *s2);
int		ft_isspace(char c);
int		ft_isalpha(char c);
int		ft_isquote(char c);
int		ft_isprint(char c);

void	*ft_calloc(size_t nb, size_t size);
void	exit_program(t_env *mini_env, int error_code);
char	*get_next_line(int fd);

int		prompt_compliance(char *str);
int		check_out_prompt(char **prompt);

int		ft_strlen(char *str);
char	*show_shell(void);

#endif
