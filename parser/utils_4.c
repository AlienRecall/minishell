/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrancav & everolla <lfrancav@student.4    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:19:48 by lfrancav &        #+#    #+#             */
/*   Updated: 2024/02/20 20:31:14 by lfrancav &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_last(t_env *env, t_env *next)
{
	t_env	*buff;

	buff = env;
	while (buff->next)
		buff = buff->next;
	buff->next = next;
}

void	add_next(t_expression **exps, t_expression *new)
{
	t_expression	*tmp;

	tmp = *exps;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

// TO DELETE
void	print_args(t_arg *args, int i)
{
	int	x;

	while (args)
	{
		x = -1;
		while (++x < i)
			printf("  ");
		printf("value: %s\n", args->value);
		x = -1;
		while (++x < i)
			printf("  ");
		args = args->next;
	}
}

// TO DELETE
void	print_exps(t_expression *exps)
{
	int	x;
	int	i;

	i = 0;
	while (exps)
	{
		x = -1;
		while (++x < i)
			printf("  ");
		printf("type: %d\n", exps->type);
		if (exps->value)
		{
			x = -1;
			while (++x < i)
				printf("  ");
			printf("value: %s\n", exps->value);
		}
		if (exps->args)
			print_args(exps->args, i);
		if (exps->type == COMMAND && exps->status != DEFAULT)
		{
			x = -1;
			while (++x < i)
				printf("  ");
			printf("status: %d\n", exps->status);
		}
		if (exps->type == PARENT_OP)
			i++;
		else if (exps->type == PARENT_CL)
			i--;
		exps = exps->next;
	}
}
