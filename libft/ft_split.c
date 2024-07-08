/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrancav & everolla <lfrancav@student.4    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:08:38 by lfrancav &        #+#    #+#             */
/*   Updated: 2024/02/20 20:08:39 by lfrancav &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wcount(const char *s, char c)
{
	int	i;
	int	wcount;

	i = 0;
	wcount = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			while (s[i] && s[i] != c)
				i++;
			wcount++;
		}
	}
	return (wcount);
}

static int	ft_wlen(const char *s, char c, int word)
{
	int	i;
	int	wcount;
	int	wlen;

	i = 0;
	wcount = 0;
	wlen = 0;
	while (s[i] && wlen == 0)
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			while (s[i] && s[i] != c)
			{
				if (s[i] && wcount == word)
					wlen++;
				i++;
			}
			wcount++;
		}
	}
	return (wlen);
}

static void	ft_strscpy(char **strs, const char *s, char c)
{
	int	i;
	int	i2;
	int	wcount;

	i = 0;
	wcount = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			i2 = 0;
			while (s[i] && s[i] != c)
			{
				strs[wcount][i2] = s[i];
				i++;
				i2++;
			}
			strs[wcount][i2] = 0;
			wcount++;
		}
	}
	strs[wcount] = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		wcount;
	int		i;

	if (!s)
		return (0);
	wcount = ft_wcount(s, c);
	strs = malloc(sizeof(char *) * (wcount + 1));
	if (!strs)
		return (0);
	i = 0;
	while (i < wcount)
	{
		strs[i] = malloc(sizeof(char) * (ft_wlen(s, c, i) + 1));
		if (!strs[i])
		{
			ft_free_2dtab(strs);
			return (0);
		}
		i++;
	}
	ft_strscpy(strs, s, c);
	return (strs);
}
