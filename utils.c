/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrancav & everolla <lfrancav@student.4    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:44:16 by lfrancav &        #+#    #+#             */
/*   Updated: 2024/02/20 21:19:32 by lfrancav &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	logic_handle_signals(t_expression *exp)
{
	if (g_signal == SIGINT)
	{
		printf("\n");
		exp->status = 130;
	}
	else if (g_signal == SIGQUIT)
	{
		printf("Quit (core dumped)\n");
		exp->status = 131;
	}
}

int	skip_op(t_expression **op)
{
	(*op) = (*op)->next;
	while ((*op) && ((*op)->type != PARENT_CL && (*op)->type != OPERATOR))
		(*op) = (*op)->next;
	return (1);
}

t_expression	*get_last_exp(t_expression *exps)
{
	if (!exps)
		return (exps);
	while (exps->next)
		exps = exps->next;
	return (exps);
}
