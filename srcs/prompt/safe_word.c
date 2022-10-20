/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferraro <vferraro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:25:59 by vferraro          #+#    #+#             */
/*   Updated: 2022/10/13 14:47:57 by vferraro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_exit_word(char *wd, int status, int print)
{
	if (!wd)
		wd = ERROR;
	if (status)
		ft_putstr_fd(wd, STDERR_FILENO);
	else if (print)
		ft_printf(wd);
	g_exit_stat = status;
	return (status);
}

int	msg_cmd_404(t_shell *sh, int i)
{
	g_exit_stat = ERR_404;
	ft_printf("%s: command not found\n", sh->in[i].elem->cont[0]);
	return (g_exit_stat);
}
