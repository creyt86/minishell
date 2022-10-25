/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferraro <vferraro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:13:29 by vferraro          #+#    #+#             */
/*   Updated: 2022/10/25 14:11:39 by vferraro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mgmnt_fd(t_shell *sh) // modifier le nom mais voir ou sont reprise et ce que ca fait
{
	int	i;
	int	j;

	i = 0;
	while (i < sh->n_cmd)
	{
		j = 0;
		while (j < sh->in[i].n_redir)
		{
			open_fd(sh, i, j);
			j++;
		}
		i++;
	}
}

void	open_fd(t_shell *sh, int i, int j)
{
	if (!ft_strncmp(sh->in[i].red[j].chevron, ">", 2))
		redir_output(sh, i, j);
	else if (!ft_strncmp(sh->in[i].red[j].chevron, "<", 2))
		redir_input(sh, i, j);
	else if (!ft_strncmp(sh->in[i].red[j].chevron, ">>", 3))
		append_in(sh, i, j);
	else if (!ft_strncmp(sh->in[i].red[j].chevron, "<<", 3))
		heredoc(sh, i, j);
}

void	init_fd(t_shell *sh)
{
	int	i;
	int	fd[2];

	sh->in[0].fd.in = STDIN_FILENO;
	sh->in[sh->n_cmd - 1].fd.out = STDOUT_FILENO;
	i = 0;
	while (i < sh->n_cmd - 1)
	{
		if (pipe(fd) == NO_RESULT)
			exit (the_end(ERR_PIPE, EXIT_FAILURE, 1));
		sh->in[i].fd.out = fd[1];
		sh->in[i + 1].fd.in = fd[0];
		i++;
	}
}

void	reset_fd(t_fd *fdk)
{
	dup2(fdk->out, STDOUT_FILENO);
	dup2(fdk->in, STDIN_FILENO);
	close(fdk->out);
	close(fdk->in);
}
