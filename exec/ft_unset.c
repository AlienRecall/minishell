/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrancav & everolla <lfrancav@student.4    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:12:45 by lfrancav &        #+#    #+#             */
/*   Updated: 2024/02/20 20:12:46 by lfrancav &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del_var_env(t_env **env, t_env *to_del)
{
	t_env	*buff;

	buff = *env;
	if (buff != to_del)
	{
		while (buff->next != to_del)
			buff = buff->next;
	}
	buff->next = to_del->next;
	free(to_del->key);
	if (to_del->value)
		free(to_del->value);
	free(to_del);
}

t_env	*find_to_del(t_env *buff, t_arg *args)
{
	int		l;
	size_t	sl;
	char	*val;

	val = args->value;
	l = ft_strlen(val);
	sl = (size_t)l;
	while (buff)
	{
		if (sl == ft_strlen(buff->key) && !ft_strncmp(buff->key, val, l))
			return (buff);
		buff = buff->next;
	}
	return (0);
}

int	ft_unset(t_expression *cmd, t_env **env)
{
	t_env	*buff;
	t_arg	*args;

	cmd->status = 0;
	if (!cmd->args)
		return (0);
	args = cmd->args;
	while (args)
	{
		buff = *env;
		buff = find_to_del(buff, args);
		if (buff)
			del_var_env(env, buff);
		args = args->next;
	}
	return (0);
}
