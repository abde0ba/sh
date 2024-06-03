/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:35:38 by abadouab          #+#    #+#             */
/*   Updated: 2024/06/03 20:31:16 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	environment_init(t_minishell *ms, char **env)
{
	ft_bzero(ms, sizeof(t_minishell));
	while (*env)
	{
        env++;
	}
}
