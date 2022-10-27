/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferraro <vferraro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:39:40 by creyt             #+#    #+#             */
/*   Updated: 2022/10/27 11:25:43 by vferraro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_sh(t_shell *sh)
{
	int	i;
	int	j;

	i = 0;
	while (i < sh->nbr_cmd)
	{
		j = 0;
		while (j < sh->in[i].nbr_elem)
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
	while (j < sh->in[i].nbr_redir)
	{
		free(sh->in[i].red[j].chevron);
		free(sh->in[i].red[j].file);
		j++;
	}
	free(sh->in[i].red);
}
