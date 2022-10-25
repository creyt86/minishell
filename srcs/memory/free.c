/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creyt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:39:40 by creyt             #+#    #+#             */
/*   Updated: 2022/10/25 10:57:17 by creyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_sh(t_shell *sh)
{
	int	i;
	int	j;

	i = 0;
	while (i < sh->n_cmd)
	{
		j = 0;
		while (j < sh->in[i].n_elem)
			free(sh->in[i].elem->cont[j++]);
		free_redir(sh, i);
		free(sh->in[i].elem->cont);
		free(sh->in[i].elem);
		i++;
	}
	free(sh->in);
}

void	free_redir(t_shell *sh, int i)
{
	int	j;

	j = 0;
	while (j < sh->in[i].n_redir)
	{
		free(sh->in[i].red[j].chevron);
		free(sh->in[i].red[j].file);
		j++;
	}
	free(sh->in[i].red);
}
