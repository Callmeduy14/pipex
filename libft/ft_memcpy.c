#include "libft.h"

// Menyalin n byte dari src ke dst. Tidak aman jika memori overlap.
void *ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *d;
	const unsigned char *s;
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	// Jika dst dan src NULL, kembalikan NULL
	if (!dst && !src)
		return NULL;
	// Salin byte per byte sebanyak n
	while (n > 0)
	{
		*d = *s;
		d++;
		s++;
		n--;
	}
	return dst;
} 