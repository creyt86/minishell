/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferraro <vferraro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:56:50 by vferraro          #+#    #+#             */
/*   Updated: 2022/10/27 11:08:38 by vferraro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_redir(t_shell *sh, int in)
{
	int	cnt;
	int	j;

	cnt = 0;
	j = 0;
	while (j < sh->in[in].n_elem)
	{
		if (ft_strncmp(sh->in[in].elem->cont[j], ">", 2) == 0)
			cnt++;
		else if (ft_strncmp(sh->in[in].elem->cont[j], "<", 2) == 0)
			cnt++;
		else if (ft_strncmp(sh->in[in].elem->cont[j], ">>", 3) == 0)
			cnt++;
		else if (ft_strncmp(sh->in[in].elem->cont[j], "<<", 3) == 0)
			cnt++;
		j++;
	}
	return (cnt);
}

void	init_redir(t_shell *sh, int in)
{
	sh->in[in].n_redir = count_redir(sh, in);
	sh->in[in].pos_red = 0;
	if (sh->in[in].n_redir > 0)
	{
		sh->in[in].red = ft_calloc(sizeof(t_redir), sh->in[in].n_redir);
		protect_malloc((char *)sh->in[in].red);
	}
	sh->in[in].n_redir = 0;
}

void	shift_elem(t_shell *sh, int in, int i)
{
	int	j;

	j = i;
	while (j < sh->in[in].n_elem)
	{
		sh->in[in].elem->cont[j] = sh->in[in].elem->cont[j + 1];
		j++;
	}
	sh->in[in].n_elem--;
}

int	pop_redir(t_shell *sh, int in, int i)
{
	int	j;

	j = sh->in[in].pos_red;
	sh->in[in].red[j].chevron = sh->in[in].elem->cont[i];
	shift_elem(sh, in, i);
	if (i < sh->in[in].n_elem)
	{
		sh->in[in].red[j].file = sh->in[in].elem->cont[i];
		shift_elem(sh, in, i);
		sh->in[in].n_redir++;
	}
	else
	{
		sh->in[in].n_redir++;
		sh->in[in].pos_red = NO_RESULT;
		return (ft_end(ERR_RDIR, ERR_REDIR, 1));
	}
	sh->in[in].pos_red++;
	return (sh->in[in].pos_red);
}

int	checker_redir(t_shell *sh, int in, int i)
{
	int	err;

	err = 0;
	if (ft_strncmp(sh->in[in].elem->cont[i], ">", 2) == 0)
	{
		err = pop_redir(sh, in, i);
	}
	else if (ft_strncmp(sh->in[in].elem->cont[i], "<", 2) == 0)
	{
		err = pop_redir(sh, in, i);
	}
	else if (ft_strncmp(sh->in[in].elem->cont[i], ">>", 3) == 0)
	{
		err = pop_redir(sh, in, i);
	}
	else if (ft_strncmp(sh->in[in].elem->cont[i], "<<", 3) == 0)
	{
		err = pop_redir(sh, in, i);
	}
	return (err);
}
