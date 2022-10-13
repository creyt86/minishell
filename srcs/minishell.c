/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferraro <vferraro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:56:12 by vferraro          #+#    #+#             */
/*   Updated: 2022/10/13 11:52:11 by vferraro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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

int	main(void)
{
	welcome_in_our_prompt();
	while (42)
	{
		ft_printf("minishell-2.0$ ");
		//ft_no_one("test");
		readline(0);
	}
	return (0);
}
