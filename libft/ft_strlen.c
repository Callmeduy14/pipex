#include "libft.h"

// Menghitung panjang string s (tidak termasuk karakter null-terminator).
size_t ft_strlen(const char *s)
{
	const char *p = s;
	while (*p)
		p++;
	// Selisih pointer p dan s adalah panjang string
	return (size_t)(p - s);
} 