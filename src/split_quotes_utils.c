/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:56:30 by yyudi             #+#    #+#             */
/*   Updated: 2025/08/14 20:40:45 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	sq_isspace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	sq_in_quote_next(int st, char c)
{
	if (c == '\'' && st != 2)
	{
		if (st == 1)
			return (0);
		return (1);
	}
	if (c == '"' && st != 1)
	{
		if (st == 2)
			return (0);
		return (2);
	}
	return (st);
}

int	sq_handle_backslash_scan(const char **pp)
{
	if (**pp == '\\' && *(*pp + 1))
	{
		*pp += 2;
		return (1);
	}
	return (0);
}
