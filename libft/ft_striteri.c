#include "libft.h"

// Melakukan operasi f pada setiap karakter string s, dengan indeks sebagai argumen.
void ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int i = 0;
	if (!s || !f)
		return;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
} 