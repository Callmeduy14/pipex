#include "libft.h"

// Menyalin n byte dari src ke dst, aman untuk overlap memori.
void *ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *d = (unsigned char *)dst;
	const unsigned char *s = (const unsigned char *)src;
	// Jika dst dan src NULL, kembalikan NULL
	if (!dst && !src)
		return NULL;
	// Jika dst di bawah src, salin maju
	if (d < s)
	{
		while (len > 0)
		{
			*d = *s;
			d++;
			s++;
			len--;
		}
	}
	// Jika dst di atas src, salin mundur
	else if (d > s)
	{
		while (len > 0)
		{
			d[len - 1] = s[len - 1];
			len--;
		}
	}
	return dst;
} 