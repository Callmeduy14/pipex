#include "libft.h"

// Membandingkan dua blok memori s1 dan s2 sebanyak n byte.
// Mengembalikan selisih byte pertama yang berbeda, atau 0 jika sama.
int ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *p1 = (const unsigned char *)s1;
	const unsigned char *p2 = (const unsigned char *)s2;
	while (n > 0)
	{
		if (*p1 != *p2)
			return (*p1 - *p2);
		p1++;
		p2++;
		n--;
	}
	return 0;
} 