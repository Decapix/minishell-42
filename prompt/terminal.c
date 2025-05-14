/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:08:17 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/08 10:58:00 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

void	restore_terminal(struct termios *old)
{
	tcsetattr(0, TCSANOW, old);
}

void	configure_terminal(struct termios *old)
{
	struct termios	new;

	tcgetattr(0, old);
	new = *old;
	new.c_lflag &= ~ISIG;
	tcsetattr(0, TCSANOW, &new);
	return ;
}
