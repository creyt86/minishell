/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_builtins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creyt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:33:11 by creyt             #+#    #+#             */
/*   Updated: 2022/10/20 13:38:19 by creyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	b_env(t_shell *sh)
{
	int	i;

	i = 0;
	while (i < sh->n_env)
	{
		if (ft_strchr(sh->env[i], '='))
			ft_printf("%s\n", sh->env[i]);
		i++;
	}
	return (the_end(NULL, EXIT_SUCCESS, 0));
}

// 'exit'		-> affiche 'exit\n' et ferme
// 'exit texte'	-> affiche 'exit\n' puis un message erreur et ferme
// exit values : celles de la commande precedente
////////////////////////////////////////

int	b_exit(t_shell *sh, int in)
{
	int	i;

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
	i = ft_atoi(sh->in[in].elem->cont[1]);
	if (i || sh->in[in].elem->cont[1][0] == '0')
	{
		free_all(sh);
		exit (the_end("exit\n", i, 0));
	}
	free_all(sh);
	exit (the_end(NOT_NUM, ERR_EXIT, 1));
}

// 'pwd'		-> affiche le chemin actuel, suivi d'un \n
// 'pwd texte	-> message d'erreur : 'pwd: too many arguments'
///////////////////////////////////////////////////////////////
int	b_pwd(t_shell *sh)
{
	char	dir[MAX_PATH];

	(void)sh;
	if (getcwd(dir, sizeof(dir)))
		ft_printf("%s\n", dir);
	return (the_end(NULL, EXIT_SUCCESS, 0));
}

void	free_all(t_shell *sh)
{
	freearray(sh->env, sh->n_env);
	free_sh(sh);
}
