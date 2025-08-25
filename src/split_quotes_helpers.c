/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:24:07 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/14 20:39:01 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

const char	*sq_skip_spaces(const char *p)
{
	while (*p && sq_isspace(*p))
		p++;
	return (p);
}

void	sq_skip_one_token(const char **pp)
{
	const char	*p;
	int			st;

	p = *pp;
	st = 0;
	while (*p)
	{
		if (sq_handle_backslash_scan(&p))
			continue ;
		st = sq_in_quote_next(st, *p);
		if (st == 0 && sq_isspace(*p))
			break ;
		p++;
	}
	*pp = p;
}

int	sq_token_span(const char *s)
{
	int	st;
	int	i;

	st = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\\' && s[i + 1])
		{
			i += 2;
			continue ;
		}
		st = sq_in_quote_next(st, s[i]);
		if (st == 0 && sq_isspace(s[i]))
			break ;
		i++;
	}
	return (i);
}

int	sq_unquote_copy(char *dst, const char *src, int n)
{
	int	st;
	int	i;
	int	k;

	st = 0;
	i = 0;
	k = 0;
	while (i < n)
	{
		if ((src[i] == '\'' && st != 2) || (src[i] == '"' && st != 1))
		{
			st = sq_in_quote_next(st, src[i]);
			i++;
			continue ;
		}
		if (src[i] == '\\' && i + 1 < n)
		{
			dst[k++] = src[i + 1];
			i += 2;
			continue ;
		}
		dst[k++] = src[i++];
	}
	dst[k] = '\0';
	return (k);
}

void	sq_free_tab(char **tab, int n)
{
	int	j;

	j = 0;
	while (j < n)
	{
		free(tab[j]);
		j++;
	}
	free(tab);
}
