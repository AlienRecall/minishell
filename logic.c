/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrancav & everolla <lfrancav@student.4    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:11:01 by lfrancav          #+#    #+#             */
/*   Updated: 2024/02/20 21:17:00 by lfrancav &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_last_parent_op_result(t_expression *actual_exp, int status)
{
	int				p;
	t_expression	*tmp;

	p = 0;
	if (status == -1)
		return ;
	tmp = actual_exp->prev;
	while (tmp)
	{
		if (tmp->type == PARENT_CL)
			p--;
		else if (tmp->type == PARENT_OP)
			p++;
		if (p == 1 && tmp->type == PARENT_OP)
		{
			tmp->status = status;
			break ;
		}
		tmp = tmp->prev;
	}
}

int	get_last_cmd_status(t_expression *cmds)
{
	t_expression	*buff;

	buff = cmds;
	while (buff)
	{
		if (buff->status != DEFAULT)
			return (buff->status);
		buff = buff->prev;
	}
	return (-1);
}

void	wait_procs(t_expression *exp, t_all *all)
{
	int				status;
	t_expression	*tmp;

	tmp = exp;
	while (tmp)
	{
		if (tmp->pid != DEFAULT)
		{
			if (tmp->status != DEFAULT)
				return ;
			waitpid(tmp->pid, &status, 0);
			tmp->status = WEXITSTATUS(status);
			logic_handle_signals(tmp);
			all->g_status = tmp->status;
			g_signal = 0;
		}
		tmp = tmp->prev;
	}
}

int	handle_operator(t_expression *op, t_all *all)
{
	wait_procs(op, all);
	if (!ft_strncmp(op->value, OR, 2))
	{
		if (!get_last_cmd_status(op))
			return (SKIP);
		else
			return (NONE);
	}
	else
	{
		if (!get_last_cmd_status(op))
			return (NONE);
		else
			return (SKIP);
	}
}

int	executor(t_all *all)
{
	int				res;
	t_expression	*tmp;

	res = 0;
	g_signal = 0;
	tmp = all->tree;
	ft_set_signals(SILENT);
	while (tmp)
	{
		if (tmp->type == PARENT_CL)
			set_last_parent_op_result(tmp, get_last_cmd_status(tmp->prev));
		else if (tmp->type == COMMAND)
			res = setup_exec(tmp, &all->envs);
		else if (tmp->type == OPERATOR && ft_strlen(tmp->value) > 1)
			if (handle_operator(tmp, all) == SKIP && skip_op(&tmp))
				continue ;
		tmp = tmp->next;
	}
	tmp = get_last_exp(all->tree);
	wait_procs(tmp, all);
	delete_heredocs();
	return (res);
}
