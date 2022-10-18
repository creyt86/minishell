/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creyt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:10:18 by creyt             #+#    #+#             */
/*   Updated: 2022/10/13 14:40:33 by creyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_shell *sh, int in, char **elem)
{
	int		i;
	char	**export;

	if (sh->in[in].n_elem == 1)
	{
		i = 0;
		while (i < sh->n_env)
		{
			export = parse_env(elem[i]);
			if (export[1])
				ft_printf("declare -x %s=\"%s\"\n", export[0], export[1]);
			else if (export[0])
				ft_printf("declare -x %s\n", export[0]);
			i++;
			freearray(export, 2);
		}
	}
}

char	**parse_env(char *s)
{
	char	**elem;

	elem = ft_split(s, '=');
	return (elem);
}

char	**dup_env(t_shell *sh)
{
	int		i;
	char	**export;

	export = malloc(sizeof(char *) * sh->n_env);
	protect_malloc((char *)export);
	i = 0;
	while (i < sh->n_env)
	{
		export[i] = ft_strdup(sh->env[i]);
		i++;
	}
	return (export);
}

void	sort_env(t_shell *sh, int in)
{
	int		i;
	int		j;
	char	*tmp;
	char	**export;

	export = dup_env(sh);
	i = 0;
	while (i < sh->n_env)
	{
		j = i + 1;
		while (j < sh->n_env)
		{
			if (ft_strncmp(export[j], export[i], MAX_PATH) < 0)
			{
				tmp = export[i];
				export[i] = export[j];
				export[j] = tmp;
			}
			j++;
		}
		i++;
	}
	print_env(sh, in, export);
	freearray(export, sh->n_env);
}

void	dup_array_to_env(t_shell *sh, char **array)
{
	int	i;

	sh->env = malloc (sizeof(char *) * (sh->n_env + 1));
	protect_malloc((char *)sh->env);
	i = -1;
	while (++i < sh->n_env)
		sh->env[i] = array[i];
	sh->env[i] = NULL;
	free(array);
}
