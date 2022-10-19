/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferraro <vferraror@student.42lausanne.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:00:11 by vferraro          #+#    #+#             */
/*   Updated: 2022/10/19 17:02:54 by vferraro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parsing_init(char *args, t_data *data)
{
	int		i;
	char	**input;

	i = 0;
	data->n_cmd = 0;
	if (args)
	{
		data->n_cmd = 1;
		if (nb_cmd(data, args, i) == NO_RESULT)
			return (NO_RESULT);
	}
	data->in = ft_calloc(sizeof(t_input), data->n_cmd + 1);
	i = -1;
	input = ft_split_ex(args, '|');
	if (parsing_misc(data, i, input) == NO_RESULT)
		return (NO_RESULT);
	freearray(input, data->n_cmd);
	return (EXIT_SUCCESS);
}

void	parsing_elem(t_data *data, char *s, int in)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s[i] && n < data->in[in].n_elem)
	{
		i += (each_elem(&data->in[in], s, i, n++));
		if (n == data->in[in].n_elem)
			break ;
		i++;
	}
	data->in[in].elem->cont[n] = NULL;
}

int	each_elem(t_input *in, char *s, int i, int n)
{
	int		j;
	char	*tmp;

	s = ft_substr(s, avoid_spaces(s, i), ft_strlen(s));
	tmp = ft_strtrim(s, " \t\n\r");
	free (s);
	s = tmp;
	i = 0;
	j = malloc_elem(in, s, i, n);
	while (i < j)
	{
		i = into_elem_quotes(in, s, i, n);
		if (s[i] == ' ')
			break ;
		in->elem->cont[n][i] = s[i];
		i++;
	}
	in->elem->cont[n][i] = '\0';
	free(s);
	return (i);
}

int	parsing_misc(t_data *data, int i, char **input)
{
	while (++i < data->n_cmd)
	{
		if (input[i] == NULL && data->n_cmd > 1)
		{
			the_end(ERR_TOKEN, ERR_REDIR, 1);
			return (NO_RESULT);
		}
		data->in[i].cont = input[i];
	}
	i = -1;
	while (++i < data->n_cmd)
	{
		data->in[i].n_elem = 1;
		count_spaces(&data->in[i], data->in[i].cont);
		data->in[i].elem = malloc(sizeof(t_elem));
		malloc_checker((char *)data->in[i].elem);
		data->in[i].elem->cont = malloc(sizeof(char *)
				* (data->in[i].n_elem + 1));
		malloc_checker((char *)data->in[i].elem->cont);
		parsing_elem(data, data->in[i].cont, i);
	}
	return (0);
}
