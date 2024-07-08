/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrancav & everolla <lfrancav@student.4    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:11:20 by lfrancav &        #+#    #+#             */
/*   Updated: 2024/02/20 20:11:22 by lfrancav &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_env **env, t_expression *cmd)
{
	t_env	*buff;
	int		fd;

	(void)cmd;
	fd = 1;
	if (!env)
		return (0);
	buff = *env;
	while (buff)
	{
		ft_putstr_fd(buff->key, fd);
		ft_putstr_fd("=", fd);
		ft_putstr_fd(buff->value, fd);
		ft_putstr_fd("\n", fd);
		buff = buff->next;
	}
	return (1);
}
