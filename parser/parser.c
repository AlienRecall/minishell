/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrancav & everolla <lfrancav@student.4    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:59:07 by lfrancav &        #+#    #+#             */
/*   Updated: 2024/02/21 22:08:41 by lfrancav &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_add_exp(t_all *all, char *input, int i[2], t_expression **last_cmd)
{
	i[1] = 0;
	if (!input[i[0]])
		return (END);
	if (input[i[0]] == '(' || input[i[0]] == ')')
		return (add_parent(&all->tree, input, &i[0]));
	i[1] = is_operator(input + i[0]);
	if (i[1] > 0)
	{
		*last_cmd = 0;
		return (add_op(&all->tree, input, i));
	}
	i[1] = is_redirection(input + i[0]);
	if (i[1] > 0)
		return (add_redir(all, input, i));
	return (add_command(all, input, &i[0], last_cmd));
}

int	build_tree(t_all *all, char *input, int i[2])
{
	int				res;
	t_expression	*last_cmd;

	last_cmd = 0;
	res = NONE;
	if (!input)
		return (EMPTY);
	while (input[i[0]])
	{
		skip_space(input, &i[0]);
		if (!input[i[0]])
			break ;
		res = parse_add_exp(all, input, i, &last_cmd);
		if (res != OK)
			break ;
	}
	return (res);
}

void	handle_errors(int code)
{
	if (code == ERROR_FILE_NOT_FOUND)
		printf("sanitizer: redirection: file not found\n");
	else if (code == ERROR_INVALID_REDIR)
		printf("parser: syntax error: invalid rediretion\n");
	else if (code == ERROR_NO_MATCHES_FOUND)
		printf("parser: No matches found\n");
	else if (code == ERROR_CANT_OPENDIR)
		printf("parser: can't open directory\n");
	else if (code == ERROR_NO_REDIR_ARG)
		printf("parser: redirection must have an argument\n");
	else if (code == ERROR_INVALID_OP)
		printf("parser: syntax error: invalid operator\n");
	else if (code == ERROR_UNCLOSED_QUOTES)
		printf("parser: syntax error: unclosed quote\n");
}

int	parse_exps(char *input, t_all *all)
{
	int	i[2];
	int	res;

	i[0] = 0;
	res = build_tree(all, input, i);
	if (res != OK)
	{
		free_exps(all->tree);
		handle_errors(res);
		return (res);
	}
	if (!(all->tree))
		return (EMPTY);
	res = sanitizer(all);
	if (res != OK)
	{
		delete_heredocs();
		free_exps(all->tree);
	}
	handle_errors(res);
	return (res);
}
