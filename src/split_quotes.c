#include "pipex.h"

static int	sk_isspace(char c){return (c == ' ' || c == '\t');}

static const char	*skip_spaces(const char *p)
{
	while (*p && sk_isspace(*p))
		p++;
	return (p);
}

static int	in_quote_next(int st, char c)
{
	if (c == '\'' && st != 2)
		return (st == 1 ? 0 : 1);
	if (c == '"' && st != 1)
		return (st == 2 ? 0 : 2);
	return (st);
}

static int	count_tokens_q(const char *s)
{
	int			cnt;
	int			st;
	const char	*p;

	cnt = 0;
	st = 0;
	p = s;
	while (*p)
	{
		p = skip_spaces(p);
		if (!*p)
			break ;
		cnt++;
		while (*p)
		{
			st = in_quote_next(st, *p);
			if (st == 0 && sk_isspace(*p))
				break ;
			p++;
		}
	}
	return (cnt);
}

static int	token_span(const char *s)
{
	int	st;
	int	len;

	st = 0;
	len = 0;
	while (s[len])
	{
		st = in_quote_next(st, s[len]);
		if (st == 0 && sk_isspace(s[len]))
			break ;
		len++;
	}
	return (len);
}

static int	unquote_copy(char *dst, const char *src, int n)
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
			st = in_quote_next(st, src[i]);
			i++;
			continue ;
		}
		dst[k++] = src[i++];
	}
	dst[k] = '\0';
	return (k);
}

char	**ft_split_quotes(const char *s)
{
	char		**tab;
	const char	*p;
	int			cnt;
	int			len;
	int			i;

	if (!s)
		return (NULL);
	cnt = count_tokens_q(s);
	tab = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (!tab)
		return (NULL);
	p = s;
	i = 0;
	while (*p && i < cnt)
	{
		p = skip_spaces(p);
		len = token_span(p);
		tab[i] = (char *)malloc((len + 1));
		if (!tab[i])
			return (free_array(tab), NULL);
		unquote_copy(tab[i++], p, len);
		p += len;
	}
	tab[i] = NULL;
	return (tab);
}
