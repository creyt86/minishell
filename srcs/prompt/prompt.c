/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferraro <vferraror@student.42lausanne.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:56:12 by vferraro          #+#    #+#             */
/*   Updated: 2022/10/19 13:11:47 by vferraro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	prompt(char **envp)
{
	t_data	data;
	int		i;

	g_exit_stat = 0;
	b_init(&data, envp);
	while (42)
	{
		if (ft_new_prompt(&data) == 1)
			continue ;
		prompt_quotes(&data);
		i = 0;
		exec_redir(&data);
		while (i < data.n_cmd)
		{
			cmd_selector(&data, i);
			i++;
		}
		ft_close(&data);
		i = 0;
		ft_wait(&data, i);
		free_data(&data);
	}
}

void	ft_close(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_cmd)
	{
		if (data->in[i].fd.out > 2)
			close(data->in[i].fd.out);
		if (data->in[i].fd.in > 2)
			close(data->in[i].fd.in);
		i++;
	}
}

int	ft_new_prompt(t_data *data)
{
	char			*prompt;
	char			*new_prompt;

	prompt = ft_set_signal();
	signal(SIGINT, SIG_IGN);
	new_prompt = ft_strtrim(prompt, " \t\n\r");
	free(prompt);
	if (!new_prompt)
	{
		freearray(data->env, data->n_env);
		exit(the_end("exit\n", EXIT_SUCCESS, 1));
	}
	if (!new_prompt[0] || parsing_init(new_prompt, data) == NO_RESULT)
	{
		free(new_prompt);
		return (1);
	}
	add_history(new_prompt);
	free(new_prompt);
	return (0);
}

void	prompt_quotes(t_data *data)
{
	int	i;
	int	j;
	int	quote;

	i = 0;
	while (i < data->n_cmd)
	{
		j = 0;
		init_redir(data, i);
		while (j < data->in[i].n_elem)
		{
			trimquotes(data, "\"", i, j);
			quote = trimquotes(data, "\'", i, j);
			if (!quote)
				conv_var(data, i, j);
			if (checker_redir(data, i, j) == NO_RESULT)
				break ;
			if (data->in[i].n_redir > 0)
				j--;
			j++;
		}
		if (data->in[i].pos_red == NO_RESULT)
			break ;
		i++;
	}
}

void	ft_wait(t_data *data, int i)
{
	while (i < data->n_cmd)
	{
		if (data->in[i].pid != NO_RESULT)
		{
			waitpid(data->in[i].pid, &g_exit_stat, 0);
			if (WIFSIGNALED(g_exit_stat))
				g_exit_stat = ERR_SIGN + g_exit_stat;
			if (WIFEXITED(g_exit_stat))
				g_exit_stat = WEXITSTATUS(g_exit_stat);
		}
		i++;
	}
}
