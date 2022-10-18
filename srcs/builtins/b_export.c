/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creyt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:05:18 by creyt             #+#    #+#             */
/*   Updated: 2022/10/13 14:40:39 by creyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_export(t_shell *sh, int in)
{
	int		i;
	char	**splited;

	if (sh->in[in].n_elem == 1)
		sort_env(sh, in);
	else
	{
		i = 1;
		while (i < sh->in[in].n_elem)
		{
			splited = parse_env(sh->in[in].elem->cont[i]);
			add_key(sh, splited[0], splited[1]);
			freearray(splited, 2);
			i++;
		}
	}
	return (the_end(NULL, EXIT_SUCCESS, 0));
}

void	update_arr(t_shell *sh, char **new_array, int add_key, char *new_val)
{
	if (add_key)
	{
		*new_array = new_val;
		*(new_array + 1) = NULL;
		sh->n_env++;
	}
	else
		new_array = NULL;
}

void	update_key(t_shell *sh, char *key, char *val, char **new_array)
{
	int		i;
	int		add_key;
	char	**exist_key;
	char	*new_val;

	i = -1;
	add_key = 1;
	new_val = define_val(key, val);
	while (++i < sh->n_env)
	{
		exist_key = parse_env(sh->env[i]);
		if (!ft_strncmp(key, exist_key[0], ft_strlen(exist_key[0])))
		{
			add_key = 0;
			if (val)
				new_array[i] = ft_strdup(new_val);
			else
				new_array[i] = ft_strdup(sh->env[i]);
			free(new_val);
		}
		else
			new_array[i] = ft_strdup(sh->env[i]);
		freearray(exist_key, 2);
	}
	update_arr(sh, &new_array[i], add_key, new_val);
}

void	add_key(t_shell *sh, char *key, char *val)
{
	char	**new_array;
	int		add_key;
	int		i;

	add_key = 1;
	new_array = ft_calloc(sizeof(char *), (sh->n_env + 2));
	protect_malloc((char *)new_array);
	i = 0;
	update_key(sh, key, val, new_array);
	freearray(sh->env, sh->n_env);
	dup_array_to_env(sh, new_array);
}

char	*define_val(char *key, char *val)
{
	char	*new_val;
	char	*new_key;
	char	*ret;

	if (val)
	{
		new_key = ft_strjoin(key, "=");
		new_val = ft_strtrim(val, "\"");
		ret = ft_strjoin(new_key, new_val);
		free(new_key);
		free(new_val);
	}
	else
		ret = ft_strdup(key);
	return (ret);
}
