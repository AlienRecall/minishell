/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrancav & everolla <lfrancav@student.4    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:11:30 by lfrancav &        #+#    #+#             */
/*   Updated: 2024/02/28 18:48:24 by lfrancav &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_arg *arg)
{
	write(1, "beeeeexit\n", 10);
	if (arg && arg->value)
	{
		if (!is_number(arg->value))
		{
			printf("minishell: exit: %s: numeric argument required\n",
				arg->value);
			arg->value = "255";
		}
		exit(ft_atoi(arg->value));
	}
	else
		exit(0);
}
