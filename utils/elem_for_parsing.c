/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_for_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferraro <vferraro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:24:31 by vferraro          #+#    #+#             */
/*   Updated: 2022/10/27 11:24:28 by vferraro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	nbr_cmd(t_shell *sh, char *args, int i)
{
	while (i < (int) ft_strlen(args))
	{
		if (args[i] == '\"' || args[i] == '\'')
		{
			i = is_quotes(args, i); // CHANGER LE NOM EN FT_QUOTES ???
			if (i == NO_RESULT)
			{
				ft_printf(NOT_CLOSE);
				return (NO_RESULT);
			}
			else if (i == 1)
			{
				ft_printf(CMD_404);
				return (NO_RESULT);
			}
		}
		if (args[i] == '|')
			sh->nbr_cmd++;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	malloc_elem(t_input *in, char *s, int i, int n)
{
	int	j;

	j = 0;
	if (s[i] == '\"' || s[i] == '\'')
			j = (is_quotes(s, i));
	else
	{
		while (i < (int) ft_strlen(s))
		{
			if (s[i] == '\"' || s[i] == '\'')
			{
				j = (is_quotes(s, i));
				i = j;
			}
			if (!s[i])
				break ;
			if (s[i] == ' ')
				break ;
			i++;
			j++;
		}
	}
	in->elem->cont[n] = malloc(sizeof(char) * (j + 2));
	protect_malloc(in->elem->cont[n]);
	return (j);
}

int	into_elem_quotes(t_input *in, char *s, int i, int n)
{
	if (s[i] == '\"' || s[i] == '\'')
	{
		in->elem->cont[n][i] = s[i];
		i++;
		if (!s[i])
			return (i);
		while (s[i] != '\"' && s[i] != '\'')
		{
			in->elem->cont[n][i] = s[i];
			i++;
		}
	}
	return (i);
}
