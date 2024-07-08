/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrancav & everolla <lfrancav@student.4    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:02:21 by lfrancav          #+#    #+#             */
/*   Updated: 2024/02/21 21:49:03 by lfrancav &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal = 0;

int	free_all(t_env *envs, t_expression *tree, char *input)
{
	if (tree)
		free_exps(tree);
	if (envs)
		free_envs(envs);
	if (input)
		free(input);
	return (0);
}

char	*prompt(t_all *all)
{
	char	*input;
	t_arg	exit_arg;

	exit_arg.value = 0;
	ft_set_signals(PROMPT);
	all->tree = 0;
	g_signal = 0;
	input = readline(SHELL_NAME);
	if (!input && !free_all(all->envs, all->tree, input))
		ft_exit(&exit_arg);
	if (ft_strlen(input) > 0)
		add_history(input);
	return (input);
}

int	main(int argc, char const *argv[], char *envp[])
{
	t_all	all;
	char	*input;

	(void)argc;
	(void)argv;
	all.g_status = 0;
	all.envs = parse_envp(envp);
	while (1)
	{
		input = prompt(&all);
		if (parse_exps(input, &all) != OK)
		{
			free_all(0, 0, input);
			continue ;
		}
		// print_exps(all.tree);
		executor(&all);
		free_all(0, all.tree, input);
	}
	return (0);
}
