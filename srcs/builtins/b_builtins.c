/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_builtins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferraro <vferraror@student.42lausanne.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:33:11 by creyt             #+#    #+#             */
/*   Updated: 2022/10/27 16:04:00 by vferraro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	b_env(t_shell *sh)
{
	int	i;

	i = 0;
	while (i < sh->nbr_env)
	{
		if (ft_strchr(sh->env_cpy[i], '='))
			ft_printf("%s\n", sh->env_cpy[i]);
		i++;
	}
	return (ft_end(NULL, EXIT_SUCCESS, 0));
}

// 'exit'		-> affiche 'exit\n' et ferme
// 'exit texte'	-> affiche 'exit\n' puis un message erreur et ferme
// exit values : celles de la commande precedente
////////////////////////////////////////

int	b_exit(t_shell *sh, int in)
{
	int	i;

	if (sh->in[in].nbr_elem == 1)
	{
		ft_printf("exit\n");
		free_all(sh);
		exit (g_exit_stat);
	}
	if (sh->in[in].nbr_elem > 2)
	{
		if (ft_atoi(sh->in[in].elem->cont[1])
			|| sh->in[in].elem->cont[1][0] == '0')
			return (ft_end(TM_ARG, EXIT_FAILURE, 1));
		free_all(sh);
		exit (ft_end(NOT_NUM, ERR_EXIT, 1));
	}
	i = ft_atoi(sh->in[in].elem->cont[1]);
	if (i || sh->in[in].elem->cont[1][0] == '0')
	{
		free_all(sh);
		exit (ft_end("exit\n", i, 0));
	}
	free_all(sh);
	exit (ft_end(NOT_NUM, ERR_EXIT, 1));
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
	return (ft_end(NULL, EXIT_SUCCESS, 0));
}

void	free_all(t_shell *sh)
{
	freetab(sh->env_cpy, sh->nbr_env);
	free_sh(sh);
}
