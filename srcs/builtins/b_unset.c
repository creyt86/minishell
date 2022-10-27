/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferraro <vferraror@student.42lausanne.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:28:43 by creyt             #+#    #+#             */
/*   Updated: 2022/10/27 16:04:00 by vferraro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_unset(t_shell *sh, int in)
{
	int		i;
	char	**tmp;

	i = 0;
	if (sh->in[in].nbr_elem == 1)
		return (ft_end(NULL, EXIT_SUCCESS, 00));
	else
	{
		i = 1;
		while (i < sh->in[in].nbr_elem)
		{
			tmp = parse_env(sh->in[in].elem->cont[i]);
			remove_key(sh, tmp[0]);
			freetab(tmp, 2);
			i++;
		}
	}
	return (ft_end(NULL, EXIT_SUCCESS, 0));
}

void	remove_key(t_shell *sh, char *key)
{
	char	**new_array;
	char	**exist_key;
	int		rem_key;
	int		i;
	int		j;

	rem_key = 0;
	new_array = malloc(sizeof(char *) * (sh->nbr_env + 1));
	protect_malloc((char *)new_array);
	i = -1;
	j = 0;
	while (++i < sh->nbr_env)
	{
		exist_key = parse_env(sh->env_cpy[i]);
		if (ft_strncmp(key, exist_key[0], ft_strlen(exist_key[0])))
			new_array[j++] = ft_strdup(sh->env_cpy[i]);
		else
			rem_key = 1;
		freetab(exist_key, 2);
	}
	new_array[j] = NULL;
	if (rem_key == 1)
		sh->nbr_env--;
	freetab(sh->env_cpy, sh->nbr_env + 1);
	dup_array_to_env(sh, new_array);
}
