#include "libft.h"

// Mengambil substring dari string s mulai dari indeks start sepanjang len karakter.
// Mengalokasikan memori baru untuk hasil substring.
char *ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t slen = 0;
	char *sub;
	size_t i = 0;
	if (!s)
		return NULL;
	while (s[slen])
		slen++;
	// Jika start di luar panjang string, kembalikan string kosong
	if (start >= slen)
		return (char *)ft_calloc(1, 1);
	// Jika len melebihi sisa karakter, sesuaikan
	if (len > slen - start)
		len = slen - start;
	// Alokasi memori untuk substring
	sub = (char *)malloc(len + 1);
	if (!sub)
		return NULL;
	// Salin karakter
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return sub;
} 