/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creyt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:10:30 by creyt             #+#    #+#             */
/*   Updated: 2022/10/13 16:12:14 by creyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	welcome_in_our_prompt(void)
{
	char	*a;
	char	*b;
	char	*c;

	a = " (|)_(|)                                       (|)_(|)";
	b = " (='.'=)      */ welcome in our prompt \\*      (='.'=)";
	c = "('')-('')                                     ('')-('')";
	ft_printf ("\n");
	ft_printf ("%s\n", a);
	ft_printf ("%s\n", b);
	ft_printf ("%s\n", c);
	ft_printf ("\n");
}

int	open_prompt(void)
{
	welcome_in_our_prompt();
	while (42)
	{
		ft_putstr_fd("minishell-2.0$ ", 1);
		//ft_printf("minishell-2.0$ ");
		//ft_exit_word("bye\n", EXIT_SUCCESS, 1);
		readline(0);
	}
	return (0);
}

int	main(void)
{
	open_prompt();
//	ft_exit_word("bye\n", EXIT_SUCCESS, 1);
}
