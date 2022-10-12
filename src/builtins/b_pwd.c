/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: creyt <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:13:37 by creyt             #+#    #+#             */
/*   Updated: 2022/10/12 15:13:59 by creyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 'pwd'		-> affiche le chemin actuel, suivi d'un \n
// 'pwd texte	-> message d'erreur : 'pwd: too many arguments'
///////////////////////////////////////////////////////////////
int	b_pwd(t_shell *sh)
{
	char	dir[MAX_PATH];

	(void)sh;
	if (getcwd(dir, sizeof(dir)))
		ft_printf("%s\n", dir);
	return (the_end(NULL, EXIT_SUCCESS, 0));
}
