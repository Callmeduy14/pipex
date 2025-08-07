#include "libft.h"

// Mencari karakter c pada string s, mengembalikan pointer ke karakter pertama yang ditemukan.
// Jika c adalah '\0', mengembalikan pointer ke akhir string.
char *ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return (char *)s;
		s++;
	}
	if ((char)c == '\0')
		return (char *)s;
	return NULL;
} 