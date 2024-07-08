/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrancav & everolla <lfrancav@student.4    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:11:02 by lfrancav &        #+#    #+#             */
/*   Updated: 2024/03/06 18:50:11 by lfrancav &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	change_current_dir(t_env **env)
{
	t_env	*buff;
	char	pwd[256];

	getcwd(pwd, 4096);
	buff = *env;
	while (buff)
	{
		if (ft_strlen(buff->key) == 3 && !ft_strncmp(buff->key, "PWD", 3))
		{
			free(buff->value);
			buff->value = ft_strdup(pwd);
			return (1);
		}
		buff = buff->next;
	}
	return (0);
}

int	ft_cd(t_expression *cmd, t_env **env)
{
	int		i;
	char	*buff;

	cmd->status = 0;
	if (!cmd->args)
	{
		buff = getenv("HOME");
		chdir(buff);
		return (0);
	}
	buff = cmd->args->value;
	i = chdir(buff);
	if (i == -1)
	{
		printf("%s%s : No such file or directory\n", SHELL_NAME, buff);
		return (1);
	}
	change_current_dir(env);
	return (0);
}
