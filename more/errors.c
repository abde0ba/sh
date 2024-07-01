/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:44:21 by abbaraka          #+#    #+#             */
/*   Updated: 2024/06/13 08:39:56 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_par(char *s)
{
	int	i;
	int	level;
	int	quotes;

	i = 0;
	level = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			(1) && (quotes = s[i], i++);
			while (s[i] && s[i] != quotes)
				i++;
		}
		if (s[i] == '\0')
			break;
		if (s[i] == '(')
		{
			level++;
			if (s[i + 1] == ')')
				return (1);
		}
		if (s[i] == ')')
			level--;
		i++;
	}
	if (level)
		return (1);
	return (0);
}

void	cleanup_handler(t_minishell *ms)
{
	clear_history();
	free(ms->read);
	cleanup(&ms->leaks);
	cleanup(&ms->alloc);
	exit(EXIT_FAILURE);
}

void	error_handler(t_minishell *ms, char *path)
{
	if (errno == ENOENT)
		syntax_err(ms, path, "No such file or directory", 1);
	else if (errno == EACCES)
			syntax_err(ms, path, "Permission denied", 1);
	else if (errno == EISDIR)
		syntax_err(ms, path, "Is a directory", 1);
	else if (errno == ENOTDIR)
		syntax_err(ms, path, "Not a directory", 1);
	else
		perror("Minishell");
}

void	execution_errors(t_minishell *ms, t_tree *tree, char *path)
{
	DIR		*dir;

	if (errno == ENOENT)
		(syntax_err(ms, path, "No such file or directory", 127), exit(127));
	if (errno == EACCES)
	{
		dir = opendir(path);
		if (dir && !closedir(dir))
			(syntax_err(ms, path, "Is a directory", 126), exit(126));
		else
			(syntax_err(ms, path, "Permission denied", 126), exit(126));
	}
	(syntax_err(ms, tree->value, "command not found", 127), exit(127));
}

void	syntax_err(t_minishell *ms, char *option, char *error_msg,
		int exit_status)
{
	char	*str;
	if (g_catch_signals != SIGINT)
	{
		if (ms->tree && !ms->tree->dis_error)
		{
			str = ft_strdup(&ms->leaks, "Minishell: ");
			// ft_putstr_fd("Minishell: ", 2);
			if (option)
			{
				str = ft_strjoin(&ms->leaks, str, option);
				str = ft_strjoin(&ms->leaks, str, ": ");
				// ft_putstr_fd(option, 2);
				// ft_putstr_fd(": ", 2);
			}
			str = ft_strjoin(&ms->leaks, str, error_msg);
			str = ft_strjoin(&ms->leaks, str, "\n");
			// ft_putstr_fd(error_msg, 2);
			// ft_putstr_fd("\n", 2);
			ft_putstr_fd(str, 2);
		}
		else if (!ms->tree)
		{
			ft_putstr_fd("Minishell: ", 2);
			ft_putstr_fd(error_msg, 2);
		}
		ms->exit_status = exit_status;
	}
}
