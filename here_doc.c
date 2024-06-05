/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadouab <abadouab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 21:18:31 by abbaraka          #+#    #+#             */
/*   Updated: 2024/06/05 11:57:09 by abadouab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_here_doc_in_child(t_minishell *ms, pid_t pid, char *delimiter, int fds[])
{
	char	*line;

	if (pid == 0)
	{
		sig_heredoc();
		while (1)
		{
			line = readline("> ");
			if (!line || (ft_strncmp(line, delimiter, ft_strlen(line)) == 0
					&& ft_strlen(line) == ft_strlen(delimiter)))
				break ;
			else
				(write(fds[0], line, ft_strlen(line)), write(fds[0], "\n", 1));
			free(line);
		}
		if (close(fds[0]) < 0)
			return (ft_putstr_fd(strerror(errno), 2), -1);
		if (close(fds[1]) < 0)
			return (ft_putstr_fd(strerror(errno), 2), -1);
		exit(0);
	}
	if (!ms->tree->syntax_err)
		ms->exit_status = 0;
	return (wait(NULL), 0);
}

int	check_token_if_redir(char *token)
{
	if (check_if_operator(token)
		&& ft_strncmp(token, ">>", ft_strlen(token))
		&& ft_strncmp(token, "<<", ft_strlen(token))
		&& ft_strncmp(token, "<", ft_strlen(token))
		&& ft_strncmp(token, ">", ft_strlen(token)))
		return (1);
	return (0);
}

int	check_syntax_err(t_minishell *ms)
{
	int	i;

	i = 0;
	while (ms->tokens[i])
	{
		if (check_if_operator(ms->tokens[i])
			&& ft_strncmp(ms->tokens[i], ">>", ft_strlen(ms->tokens[i]))
			&& ft_strncmp(ms->tokens[i], "<<", ft_strlen(ms->tokens[i]))
			&& ft_strncmp(ms->tokens[i], "<", ft_strlen(ms->tokens[i]))
			&& ft_strncmp(ms->tokens[i], ">", ft_strlen(ms->tokens[i])))
			return (syntax_err(ms, "syntax error", 258), 1);
		i++;
	}
	return (0);
}

int	ft_open_here_doc(t_minishell *ms, char *delimiter)
{
	int		fds[2];
	int		len;
	pid_t	pid;

	unlink("here_doc");
	fds[0] = open("here_doc", O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (fds[0] < 0)
		return (ft_putstr_fd(strerror(errno), 2), -1);
	fds[1] = open("here_doc", O_RDONLY, 0644);
	if (fds[1] < 0)
		return (ft_putstr_fd(strerror(errno), 2), -1);
	(1) && (unlink("here_doc"), len = ft_strlen(delimiter), pid = fork());
	if (pid < 0)
		return (-1);
	if (ft_here_doc_in_child(ms, pid, delimiter, fds) == -1)
		return (-1);
	if (g_sig == SIGINT)
		ms->exit_status = 1;
	if (close(fds[0]) < 0)
		return (ft_putstr_fd(strerror(errno), 2), -1);
	return (fds[1]);
}
