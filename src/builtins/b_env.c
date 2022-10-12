/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creyt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:08:01 by creyt             #+#    #+#             */
/*   Updated: 2022/10/12 15:09:59 by creyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_all(t_shell *sh)
{
	freearray(sh->env, sh->n_env);
	free_data(sh);
}