#include "libft.h"

// Membuat string baru hasil transformasi setiap karakter s dengan fungsi f.
char *ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int i = 0;
	char *res;
	if (!s || !f)
		return NULL;
	while (s[i])
		i++;
	// Alokasi memori untuk string hasil
	res = (char *)malloc(i + 1);
	if (!res)
		return NULL;
	for (unsigned int j = 0; j < i; j++)
		res[j] = f(j, s[j]);
	res[i] = '\0';
	return res;
} 