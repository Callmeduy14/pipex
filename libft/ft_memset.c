#include "libft.h"

// Fungsi ini mengisi blok memori dengan nilai tertentu (c) sebanyak len byte.
void *ft_memset(void *b, int c, size_t len)
{
	unsigned char *ptr;
	ptr = (unsigned char *)b;
	// Ulangi sebanyak len, isi setiap byte dengan nilai c
	while (len > 0)
	{
		*ptr = (unsigned char)c;
		ptr++;
		len--;
	}
	// Kembalikan pointer awal
	return b;
} 