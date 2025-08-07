#include "libft.h"

// Mencari karakter c pada blok memori s sebanyak n byte.
// Mengembalikan pointer ke lokasi karakter jika ditemukan, NULL jika tidak.
void *ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char *ptr = (const unsigned char *)s;
	unsigned char uc = (unsigned char)c;
	while (n > 0)
	{
		if (*ptr == uc)
			return (void *)ptr;
		ptr++;
		n--;
	}
	return NULL;
} 