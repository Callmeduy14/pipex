/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 19:32:20 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/14 20:34:56 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	count_tokens_q(const char *s)
{
	const char	*p;
	int			cnt;

	p = s;
	cnt = 0;
	while (*p)
	{
		p = sq_skip_spaces(p);
		if (!*p)
			break ;
		cnt++;
		sq_skip_one_token(&p);
	}
	return (cnt);
}

static int	sq_fill_tokens(char **tab, const char *s, int cnt)
{
	const char	*p;
	int			i;
	int			len;

	i = 0;
	p = s;
	while (*p && i < cnt)
	{
		p = sq_skip_spaces(p);
		len = sq_token_span(p);
		tab[i] = (char *)malloc(len + 1);
		if (!tab[i])
		{
			sq_free_tab(tab, i);
			return (0);
		}
		sq_unquote_copy(tab[i], p, len);
		p += len;
		i++;
	}
	tab[i] = NULL;
	return (1);
}

char	**ft_split_quotes(const char *s)
{
	char	**tab;
	int		cnt;

	if (!s)
		return (NULL);
	cnt = count_tokens_q(s);
	tab = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (!tab)
		return (NULL);
	if (!sq_fill_tokens(tab, s, cnt))
		return (NULL);
	return (tab);
}
