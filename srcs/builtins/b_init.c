 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creyt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:09:39 by creyt             #+#    #+#             */
/*   Updated: 2022/10/13 14:40:41 by creyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_init(t_shell *sh, char *envp[])
{
	int		i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	sh->nbr_env = i;
	sh->env_cpy = malloc(sizeof(char *) * (sh->nbr_env + 1));
	protect_malloc((char *)sh->env_cpy);
	i = 0;
	while (i < sh->nbr_env)
	{
		sh->env_cpy[i] = ft_strdup(envp[i]);
		protect_malloc(sh->env_cpy[i++]);
	}
	sh->env_cpy[i] = NULL;
}

void	protect_malloc(char *s)
{
	if (!s)
		exit(ft_end(ERR_MALL, EXIT_FAILURE, 1));
}