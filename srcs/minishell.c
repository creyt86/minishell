/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferraro <vferraro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:56:12 by vferraro          #+#    #+#             */
/*   Updated: 2022/10/20 11:34:11 by vferraro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	welcome_in_our_prompt(void)
{
	char	*a;
	char	*b;
	char	*c;

	a = " (|)_(|)";
	b = " (='.'=)     */ welcome in our prompt \\*";
	c = "('')-('')";
	ft_printf ("\n");
	ft_printf ("%s\n", a);
	ft_printf ("%s\n", b);
	ft_printf ("%s\n", c);
	ft_printf ("\n");
}

int	main(int argc, char *argv[], char **envp)
{
	(void)argv;
	(void)envp;
	if (argc > 1)
	{
		ft_printf("\033[31mARG_ERROR\n\033[31m");
		return (1);
	}
	if (envp)
	{
		welcome_in_our_prompt();
		prompt(envp);
	}
}
