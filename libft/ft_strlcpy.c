#include "libft.h"

// Menyalin string src ke dst sebanyak dstsize-1 karakter, lalu null-terminate.
// Mengembalikan panjang string src.
size_t ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t i = 0;
	if (dstsize > 0)
	{
		// Salin karakter satu per satu hingga dstsize-1 atau src habis
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	// Hitung panjang src
	i = 0;
	while (src[i])
		i++;
	return i;
} 