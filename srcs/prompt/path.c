/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferraro <vferraro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:13:25 by vferraro          #+#    #+#             */
/*   Updated: 2022/10/20 10:45:31 by vferraro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* Check if we have permission to access the str and if it start with PATH */
int	u_should_not_path(char **env, char *str)
{
	int	i;

	i = 0;
	if (access(str, (X_OK)) == 0)
		return (2);
	while (env[i])
	{
		if (ft_strncmp("PATH", env[i], 4) == 0)
			return (0);
		i++;
	}
	return (1);
}
