/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrancav & everolla <lfrancav@student.4    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:07:47 by lfrancav &        #+#    #+#             */
/*   Updated: 2024/02/20 21:17:59 by lfrancav &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	match_wildcard(char *str, char **pref_suf)
{
	int	len;
	int	preflen;
	int	suflen;

	len = ft_strlen(str);
	if (len == 1 && ft_strncmp(str, ".", 1) == 0)
		return (0);
	if (len == 2 && ft_strncmp(str, "..", 2) == 0)
		return (0);
	preflen = ft_strlen(pref_suf[0]);
	suflen = ft_strlen(pref_suf[1]);
	if (preflen > 0 && ft_strncmp(str, pref_suf[0], preflen) != 0)
		return (0);
	if (suflen > 0 && ft_strncmp(&str[len - suflen], pref_suf[1], suflen) != 0)
		return (0);
	return (1);
}

int	alloc_wildcard(char **pref_suf, char ***res)
{
	int				i;
	DIR				*folder;
	struct dirent	*entry;

	folder = opendir(".");
	if (!folder)
		return (ERROR_CANT_OPENDIR);
	i = 0;
	entry = readdir(folder);
	while (entry)
	{
		if (match_wildcard(entry->d_name, pref_suf))
			i++;
		entry = readdir(folder);
	}
	closedir(folder);
	*res = (char **)malloc(sizeof(char *) * i + 1);
	if (!*res)
		return (MALLOC_ERROR);
	(*res)[i] = 0;
	return (i);
}

int	get_prefix_suffix(char ***pref_suf, char *value)
{
	int	i;
	int	l;

	*pref_suf = (char **)malloc(sizeof(char *) * 2);
	if (!*pref_suf)
		return (MALLOC_ERROR);
	if (!value)
		return (0);
	i = -1;
	while (value[++i])
		if (value[i] == WILDCARD)
			break ;
	l = 1;
	if (!value[i])
		l = 0;
	(*pref_suf)[0] = ft_substr(value, 0, i);
	(*pref_suf)[1] = ft_substr(value, i + l, ft_strlen(value) - i + l);
	return (i);
}

/*
i[0]: wildcard index
i[1]: res counter
*/
int	expand_wildcard(char *value, char ***res)
{
	int				i[2];
	DIR				*folder;
	char			**pref_suf;
	struct dirent	*entry;

	folder = opendir(".");
	if (!folder)
		return (ERROR_CANT_OPENDIR);
	i[0] = get_prefix_suffix(&pref_suf, value);
	alloc_wildcard(pref_suf, res);
	i[1] = 0;
	entry = readdir(folder);
	while (entry)
	{
		if (match_wildcard(entry->d_name, pref_suf))
			(*res)[i[1]++] = ft_strdup(entry->d_name);
		entry = readdir(folder);
	}
	closedir(folder);
	free(pref_suf[0]);
	free(pref_suf[1]);
	free(pref_suf);
	return (OK);
}
