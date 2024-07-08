/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrancav & everolla <lfrancav@student.4    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:11:46 by lfrancav &        #+#    #+#             */
/*   Updated: 2024/02/28 22:44:49 by lfrancav &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_expression *cmd)
{
	int		fd;
	char	cwd[256];

	(void)cmd;
	fd = 1;
	getcwd(cwd, 4096);
	ft_putstr_fd(cwd, fd);
	write(fd, "\n", 1);
	return (1);
}
