/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creyt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:27:10 by creyt             #+#    #+#             */
/*   Updated: 2022/10/25 13:40:36 by creyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_exit_word(char *msg, int status, int print)
{
	if (!msg)
		msg = ERROR;
	if (status)
		ft_putstr_fd(msg, STDERR_FILENO);
	else if (print)
		ft_printf(msg);
	g_exit_stat = status;
	return (status);
}

int	msg_cmd_404(t_data *dt, int i)
{
	g_exit_stat = ERR_404;
	ft_printf("%s: command not found\n", dt->in[i].elem->cont[0]);
	return (g_exit_stat);
}
