/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creyt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:27:30 by creyt             #+#    #+#             */
/*   Updated: 2022/10/12 15:07:48 by creyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int b_cd(t_shell *sh, int in)
{
    char	dir[MAX_PATH];
	int		i;

	if (sh->in[in].n_elem == 1)
	{
		no_place_like_home(sh);
		i = 0;
	}
	else
		i = 1;
	if (i)
	{
		if (sh->in[in].elem->cont[i][0] == '-')
			i = print_cd(OPT_IGN, 2);
		if (i >= sh->in[in].n_elem)
			return (the_end(ERR_NO_ARG, EXIT_FAILURE, 1));
		if (chdir(sh->in[in].elem->cont[i]))
			return (the_end(ERROR, EXIT_FAILURE, 1));
	}
	update_env(sh, dir);
	return (the_end(NULL, EXIT_SUCCESS, 0));
}
void	update_env(t_shell *sh, char *dir)
{
	int		i;
	int		j;
	char	**splited;

	i = where_in_env(sh, "PWD", 3);
	j = where_in_env(sh, "OLDPWD", 6);
	if (i == NO_RESULT)
		ft_printf(CMD_404);
	else
	{
		free(sh->env[j]);
		splited = parse_env(sh->env[i]);
		sh->env[j] = ft_strjoin("OLDPWD=", splited[1]);
		freearray(splited, 2);
		free(sh->env[i]);
		sh->env[i] = ft_strjoin("PWD=", getcwd(dir, MAX_PATH));
	}
}

int	where_in_env(t_shell *sh, char *key, int len)
{
	int	i;
	int	diff;

	i = 0;
	while (i < sh->n_env)
	{
		diff = ft_strncmp(sh->env[i], key, len + 1);
		if (diff == 0 || diff == 61)
			return (i);
		i++;
	}
	return (NO_RESULT);
}

int	print_cd(char *s, int i)
{
	ft_printf(s);
	return (i);
}

int	no_place_like_home(t_shell *sh)
{
	int		i;
	char	**tmp;

	i = where_in_env(sh, "HOME", 5);
	if (i == NO_RESULT)
		the_end(HOMELESS, EXIT_FAILURE, 1);
	else
	{
		tmp = parse_env(sh->env[i]);
		if (chdir(tmp[1]))
			the_end(ERROR, EXIT_FAILURE, 1);
		freearray(tmp, 2);
	}
	return (the_end(NULL, EXIT_SUCCESS, 0));
}