/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: |||||||| <||||||||@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:55:24 by ||||||||          #+#    #+#             */
/*   Updated: 2024/06/11 14:46:14 by ||||||||         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_minishell *ms, t_environ *env)
{
	while (env)
	{
		if (env->val)
			ft_printf("%s=%s\n", env->var, env->val);
		env = env->next;
	}
	ms->exit_status = 0;
}
