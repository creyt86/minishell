/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferraro <vferraro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 13:52:28 by vferraro          #+#    #+#             */
/*   Updated: 2022/10/20 13:55:14 by vferraro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_redir(t_shell *sh)
{
	init_fd(sh);
	mgmnt_fd(sh);
}

// '<'
void	redir_input(t_shell *sh, int i, int j)
{
	int	fd;

	fd = open(sh->in[i].red[j].file, O_RDONLY);
	if (fd == NO_RESULT)
		the_end(ERR_FILE, EXIT_FAILURE, 1);
	else
	{
		if (sh->in[i].fd.in > 2)
			close(sh->in[i].fd.in);
		sh->in[i].fd.in = fd;
	}
}

// '>'
void	redir_output(t_shell *sh, int i, int j)
{
	int	fd;

	fd = open(sh->in[i].red[j].file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == NO_RESULT)
		the_end(ERR_FILE, EXIT_FAILURE, 1);
	else
	{
		if (sh->in[i].fd.out > 2)
			close(sh->in[i].fd.out);
		sh->in[i].fd.out = fd;
	}
}

// '>>'
void	append_in(t_shell *sh, int i, int j)
{
	int	fd;

	fd = open(sh->in[i].red[j].file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd == NO_RESULT)
		the_end(ERR_FILE, EXIT_FAILURE, 1);
	else
	{
		if (sh->in[i].fd.out > 2)
			close(sh->in[i].fd.out);
		sh->in[i].fd.out = fd;
	}
}

// '<<'
void	heredoc(t_shell *sh, int i, int j)
{
	int		fd[2];
	char	*keyword;
	char	*prompt;

	if (pipe(fd) == NO_RESULT)
		the_end(ERR_PIPE, EXIT_FAILURE, 1);
	keyword = sh->in[i].red[j].file;
	prompt = NULL;
	while (1)
	{
		prompt = readline("> ");
		if (!prompt)
			break ;
		if (ft_strncmp(prompt, keyword, (ft_strlen(keyword) + 1)))
			ft_putendl_fd(prompt, fd[1]);
		else
			break ;
		free(prompt);
	}
	free(prompt);
	close(fd[1]);
	if (sh->in[i].fd.in > 2)
		close(sh->in[i].fd.in);
	sh->in[i].fd.in = fd[0];
}