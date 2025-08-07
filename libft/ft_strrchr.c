#include "libft.h"

// Mencari karakter c pada string s, mengembalikan pointer ke karakter terakhir yang ditemukan.
// Jika c adalah '\0', mengembalikan pointer ke akhir string.
char *ft_strrchr(const char *s, int c)
{
	const char *last = NULL;
	while (*s)
	{
		if (*s == (char)c)
			last = s;
		s++;
	}
	if ((char)c == '\0')
		return (char *)s;
	return (char *)last;
} 