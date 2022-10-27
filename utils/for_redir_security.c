/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_redir_security.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferraro <vferraro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:09:16 by vferraro          #+#    #+#             */
/*   Updated: 2022/10/27 11:09:58 by vferraro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	more_security(t_shell *sh, int i)
{
	if (sh->in[i].fd.in > 2)
		close(sh->in[i].fd.in);
}
