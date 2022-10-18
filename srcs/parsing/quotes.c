/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creyt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:48:05 by creyt             #+#    #+#             */
/*   Updated: 2022/10/13 15:03:56 by creyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	double_quotes(t_input *in, char *s, int i, int n)
{
	int		k;
	int		size;
	int		j;

	k = 0;
	size = 1;
	j = i;
	while (s[i] != ' ' && s[i])
	{
		size++;
		i++;
	}
	i = j;
	in->elem->cont[n] = malloc(sizeof(char) * size);
	protect_malloc(in->elem->cont[n]);
	while (s[i] && s[i] != ' ')
		in->elem->cont[n][k++] = s[i++];
	if (i == 1)
		in->elem->cont[n][k] = ' ';
	return (i + 1);
}

int	simple_quotes(t_input *in, char *s, int i, int n)
{
	int		k;
	int		size;
	int		j;

	k = 0;
	size = 0;
	j = i;
	while (s[i] && s[i] != '\'')
	{
		size++;
		i++;
	}
	i = j;
	in->elem->cont[n] = malloc(sizeof(char) * size);
	protect_malloc(in->elem->cont[n]);
	while (s[i] && s[i] != '\'')
		in->elem->cont[n][k++] = s[i++];
	if (i == 1)
		in->elem->cont[n][k] = ' ';
	return (i + 1);
}

int	no_quote(t_input *in, char *s, int i, int n)
{
	int		k;
	int		size;
	int		j;

	k = 0;
	size = 0;
	j = i;
	while (s[i] && s[i] != ' ')
	{
		size++;
		i++;
	}
	i = j;
	in->elem->cont[n] = malloc(sizeof(char) * (size + 1));
	protect_malloc(in->elem->cont[n]);
	while (s[i] && s[i] != ' ')
		in->elem->cont[n][k++] = s[i++];
	in->elem->cont[n][k] = '\0';
	return (i);
}
