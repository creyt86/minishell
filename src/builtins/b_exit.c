/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creyt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:12:04 by creyt             #+#    #+#             */
/*   Updated: 2022/10/12 15:13:04 by creyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 'exit'		-> affiche 'exit\n' et ferme
// 'exit texte'	-> affiche 'exit\n' puis un message erreur et ferme
// exit values : celles de la commande precedente
////////////////////////////////////////

int	b_exit(t_shell *sh, int in)
{
	int	n;

	if (sh->in[in].n_elem == 1)
	{
		ft_printf("exit\n");
		free_all(sh);
		exit (g_exit_stat);
	}
	if (sh->in[in].n_elem > 2)
	{
		if (ft_atoi(sh->in[in].elem->cont[1])
			|| sh->in[in].elem->cont[1][0] == '0')
			return (the_end(TM_ARG, EXIT_FAILURE, 1));
		free_all(sh);
		exit (the_end(NOT_NUM, ERR_EXIT, 1));
	}
	n = ft_atoi(sh->in[in].elem->cont[1]);
	if (n || sh->in[in].elem->cont[1][0] == '0')
	{
		free_all(sh);
		exit (the_end("exit\n", n, 0));
	}
	free_all(sh);
	exit (the_end(NOT_NUM, ERR_EXIT, 1));
}