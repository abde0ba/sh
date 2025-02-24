/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbaraka <abbaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:39:11 by abbaraka          #+#    #+#             */
/*   Updated: 2024/07/16 01:23:59 by abbaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*parse_side(t_minishell *ms, int *i)
{
	t_tree	*exp;

	if (ms->tokens[*i]
		&& ft_strncmp(ms->tokens[*i], ")", ft_strlen(ms->tokens[*i])) == 0)
		return (syntax_err(ms, NULL,
				"syntax error near unexpected token `)'\n", 258),
			NULL);
	else if (ms->tokens[*i]
		&& ft_strncmp(ms->tokens[*i], "(", ft_strlen(ms->tokens[*i])) == 0)
	{
		(*i)++;
		exp = parse_exp(ms, i, 0);
		return (exp);
	}
	return (parse_simple_command(ms, i));
}

t_tree	*make_tree(t_minishell *ms, t_tree *left, t_tree *right, char *op)
{
	t_tree	*node;

	node = allocate(&ms->leaks, 1, sizeof(t_tree));
	if (!node)
		cleanup_handler(ms);
	set_op(node, op);
	if (ft_strncmp(op, "|", ft_strlen(op)) == 0
		&& ft_strlen(op) == ft_strlen("|"))
	{
		if (left->type == PIPE_T)
		{
			ft_treeadd_back(&left, right);
			return (left);
		}
		node->value = op;
		node->type = PIPE_T;
		node->left = NULL;
		node->right = NULL;
		ft_treeadd_back(&node, left);
		ft_treeadd_back(&node, right);
		return (node);
	}
	if (ft_strncmp(op, "||", ft_strlen(op)) == 0
		&& ft_strlen(op) == ft_strlen("||"))
		node->type = OR_T;
	if (ft_strncmp(op, "&&", ft_strlen(op)) == 0
		&& ft_strlen(op) == ft_strlen("&&"))
		node->type = AND_T;
	node->value = op;
	node->left = left;
	node->right = right;
	return (node);
}

int	check_if_prec(char *token)
{
	if ((ft_strncmp(token, "||", ft_strlen(token)) == 0
			&& ft_strlen(token) == ft_strlen("||"))
		|| (ft_strncmp(token, "&&", ft_strlen(token)) == 0
			&& ft_strlen(token) == ft_strlen("&&")))
		return (0);
	return (1);
}

t_tree	*parse_exp(t_minishell *ms, int *i, int min_pr)
{
	char		*op;
	t_tree		*left;
	t_tree		*right;

	left = parse_side(ms, i);
	if (!left)
		return (NULL);
	if (!ms->tokens[*i])
		return (left);
	if (ms->tokens[*i] && check_token_op(ms->tokens[*i]))
		(*i)--;
	while (ms->tokens[*i] && ms->tokens[*i + 1]
		&& check_token_op(ms->tokens[*i + 1])
		&& min_pr <= check_if_prec(ms->tokens[*i + 1]))
	{
		op = ms->tokens[*i + 1];
		(*i) += 2;
		if (!ms->tokens[*i] || check_token_op(ms->tokens[*i]))
			return (syntax_err(ms, NULL, "syntax error", 258), NULL);
		right = parse_exp(ms, i, check_if_prec(op) + 1);
		left = make_tree(ms, left, right, op);
	}
	return (left);
}

t_tree	*parse_tree(t_minishell *ms)
{
	int			i;
	int			j;

	if (!ms->tokens || !ms->tokens[0])
		return (NULL);
	i = 0;
	j = 0;
	ms->tree = allocate(&ms->leaks, 1, sizeof(t_tree));
	if (!ms->tree)
		cleanup_handler(ms);
	ms->tree = parse_exp(ms, &i, 0);
	if (check_closed_quotes(ms, 0, 0))
		return (NULL);
	return (ms->tree);
}
