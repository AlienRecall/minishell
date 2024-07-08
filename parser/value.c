/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrancav & everolla <lfrancav@student.4    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:04:31 by lfrancav &        #+#    #+#             */
/*   Updated: 2024/02/20 21:17:53 by lfrancav &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// add check
char	*alloc_value(t_all *all, char *value)
{
	int		i[2];
	char	*res;

	i[0] = 0;
	i[1] = 0;
	while (value[i[0]])
	{
		if (value[i[0]] == QUOTE_D || value[i[0]] == QUOTE_S)
			solve_quote(all, value, i, 0);
		else if (value[i[0]] == DOLLAR && !stop_parse_dollar(value + (i[0]
					+ 1)))
			expand_dollar(all, value, i, 0);
		else if (i[0]++ >= 0 && i[1]++ >= 0)
			continue ;
	}
	res = (char *)malloc(sizeof(char) * i[1] + 1);
	res[i[1]] = 0;
	return (res);
}

char	*solve_value_body(t_all *all, char *value, int *has_wildcard, int hd)
{
	int		i[2];
	char	*res;

	i[0] = 0;
	i[1] = 0;
	res = alloc_value(all, value);
	if (!res)
		return (res);
	while (value[i[0]])
	{
		if (!hd && (value[i[0]] == QUOTE_D || value[i[0]] == QUOTE_S))
			solve_quote(all, value, i, res);
		else if (value[i[0]] == DOLLAR && !stop_parse_dollar(value + (i[0]
					+ 1)))
			expand_dollar(all, value, i, res);
		else
			res[i[1]++] = value[i[0]++];
		if (value[i[0] - 1] == WILDCARD)
			*has_wildcard = 1;
	}
	return (res);
}

int	solve_value(t_all *all, char *value, char ***res)
{
	int		r;
	int		has_wildcard;
	char	*tmp;

	r = OK;
	has_wildcard = 0;
	tmp = solve_value_body(all, value, &has_wildcard, 0);
	if (has_wildcard)
	{
		r = expand_wildcard(tmp, res);
		free(tmp);
		if (r != OK)
			return (r);
		if (*res)
			return (OK);
		free(res);
		return (ERROR_NO_MATCHES_FOUND);
	}
	*res = (char **)malloc(sizeof(char *) * 2);
	if (!*res)
		return (MALLOC_ERROR);
	(*res)[0] = tmp;
	(*res)[1] = 0;
	return (r);
}

int	add_value(t_expression **exp, t_all *all, char *str, int *c)
{
	int		i;
	int		res;
	char	**v;

	if (!str || ft_strlen(str) == 0)
		return (OK);
	res = solve_value(all, str, &v);
	if (res != OK)
	{
		free_mtx(v);
		free(str);
		return (res);
	}
	i = -1;
	while (v[++i])
	{
		if (ft_strlen(v[i]) > 0 && *c == 0 && ++(*c) > 0)
			(*exp)->value = ft_strdup(v[i]);
		else if (ft_strlen(v[i]) > 0)
			add_arg(&(*exp)->args, ft_strdup(v[i]));
	}
	free_mtx(v);
	free(str);
	return (res);
}
