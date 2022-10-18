/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creyt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:28:43 by creyt             #+#    #+#             */
/*   Updated: 2022/10/13 14:39:53 by creyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_unset(t_shell *sh, int in)
{
	int		i;
	char	**splited;

	i = 0;
	if (sh->in[in].n_elem == 1)
		return (the_end(NULL, EXIT_SUCCESS, 00));
	else
	{
		i = 1;
		while (i < sh->in[in].n_elem)
		{
			splited = parse_env(sh->in[in].elem->cont[i]);
			remove_key(sh, splited[0]);
			freearray(splited, 2);
			i++;
		}
	}
	return (the_end(NULL, EXIT_SUCCESS, 0));
}

void	remove_key(t_shell *sh, char *key)
{
	char	**new_array;
	char	**exist_key;
	int		rem_key;
	int		i;
	int		j;

	rem_key = 0;
	new_array = malloc(sizeof(char *) * (sh->n_env + 1));
	protect_malloc((char *)new_array);
	i = -1;
	j = 0;
	while (++i < sh->n_env)
	{
		exist_key = parse_env(sh->env[i]);
		if (ft_strncmp(key, exist_key[0], ft_strlen(exist_key[0])))
			new_array[j++] = ft_strdup(sh->env[i]);
		else
			rem_key = 1;
		freearray(exist_key, 2);
	}
	new_array[j] = NULL;
	if (rem_key == 1)
		sh->n_env--;
	freearray(sh->env, sh->n_env + 1);
	dup_array_to_env(sh, new_array);
}
