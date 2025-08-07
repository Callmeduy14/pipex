#include "libft.h"

// Mencari substring needle pada haystack, maksimal len karakter.
// Mengembalikan pointer ke awal substring jika ditemukan, NULL jika tidak.
char *ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t nlen = 0;
	size_t i;

	if (*needle == '\0')
		return (char *)haystack;
	while (needle[nlen])
		nlen++;
	while (*haystack && len >= nlen)
	{
		i = 0;
		while (i < nlen && haystack[i] == needle[i])
			i++;
		if (i == nlen)
			return (char *)haystack;
		haystack++;
		len--;
	}
	return NULL;
} 