#include "libft.h"

// Menyalin byte dari src ke dst hingga menemukan karakter c atau n byte.
// Jika karakter c ditemukan, kembalikan pointer setelah c di dst, jika tidak NULL.
void *ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char *d = (unsigned char *)dst;
	const unsigned char *s = (const unsigned char *)src;
	unsigned char uc = (unsigned char)c;
	while (n > 0)
	{
		*d = *s;
		if (*s == uc)
			return (void *)(d + 1);
		d++;
		s++;
		n--;
	}
	return NULL;
} 