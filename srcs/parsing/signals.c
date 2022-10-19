/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferraro <vferraror@student.42lausanne.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:40:24 by vferraro          #+#    #+#             */
/*   Updated: 2022/10/19 15:56:13 by vferraro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_set_signal(void)
{
	struct termios	replace;
	struct termios	saved;
	char			*prompt;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_int);
	tcgetattr(STDIN_FILENO, &saved);
	tcgetattr(STDIN_FILENO, &replace);
	replace.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &replace);
	prompt = readline("minishell-2.0$ ");
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &saved);
	return (prompt);
}

void	sig_int(int c)
{
	if (c == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_double(int c)
{
	if (c == SIGINT)
	{
		write(1, "\n", 1);
	}
	if (c == SIGQUIT)
	{
		ft_printf("Quit : %d\n", c);
		rl_on_new_line();
	}
}
