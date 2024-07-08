/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_parent_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrancav & everolla <lfrancav@student.4    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:58:59 by lfrancav &        #+#    #+#             */
/*   Updated: 2024/02/28 19:18:43 by lfrancav &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_redir(t_expression *exp, t_all *all, char *input, int i[2])
{
	char	*tmp;
	int		has_wildcard;
	int		res;

	has_wildcard = 0;
	tmp = 0;
	exp->value = ft_substr(input, i[0], i[1]);
	i[0] += i[1];
	if (is_operator(input + (i[0])) || is_redirection(input + i[0]))
		return (ERROR_INVALID_REDIR);
	skip_space(input, &i[0]);
	res = take_str(input, &(i[0]), &tmp);
	if (res != OK)
		return (ERROR_UNCLOSED_QUOTES);
	if (!tmp)
		return (ERROR_NO_REDIR_ARG);
	add_arg(&exp->args, solve_value_body(all, tmp, &has_wildcard, 0));
	free(tmp);
	return (OK);
}

int	add_redir(t_all *all, char *input, int i[2])
{
	int				res;
	t_expression	*new;

	if (alloc_default_exp(&new, REDIRECTION) != OK)
		return (MALLOC_ERROR);
	res = parse_redir(new, all, input, i);
	if (res != OK)
	{
		free_exps(new);
		return (res);
	}
	if (!all->tree)
	{
		all->tree = new;
		return (OK);
	}
	add_next(&(all->tree), new);
	return (OK);
}

int	parse_op(char *input, int i)
{
	if (i == 1)
		return (OK);
	if (*(input + i) == '&' || *(input + i) == '|')
		return (ERROR_INVALID_OP);
	return (OK);
}

int	add_op(t_expression **exps, char *input, int i[2])
{
	t_expression	*new;

	if (alloc_default_exp(&new, OPERATOR) != OK)
		return (MALLOC_ERROR);
	new->value = ft_substr(input, i[0], i[1]);
	if (parse_op(input + i[0], i[1]) != (OK))
	{
		free_exps(new);
		return (ERROR_INVALID_OP);
	}
	i[0] += i[1];
	if (!*exps)
	{
		*exps = new;
		return (OK);
	}
	add_next(exps, new);
	return (OK);
}

int	add_parent(t_expression **exps, char *input, int *i)
{
	t_expression	*new;

	if (alloc_default_exp(&new, DEFAULT) != OK)
		return (MALLOC_ERROR);
	if (input[*i] == '(')
		new->type = PARENT_OP;
	else
		new->type = PARENT_CL;
	(*i)++;
	if (!*exps)
	{
		*exps = new;
		return (OK);
	}
	add_next(exps, new);
	return (OK);
}
