#include "libft.h"

// Menambahkan string src ke akhir dst, maksimal dstsize-1 karakter, lalu null-terminate.
// Mengembalikan panjang awal dst + panjang src.
size_t ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t dlen = 0;
	size_t slen = 0;
	size_t i = 0;

	// Hitung panjang dst dan src
	while (dst[dlen] && dlen < dstsize)
		dlen++;
	while (src[slen])
		slen++;
	// Jika dst penuh, kembalikan dstsize + panjang src
	if (dlen == dstsize)
		return dstsize + slen;
	// Tambahkan src ke dst
	while (src[i] && dlen + i < dstsize - 1)
	{
		dst[dlen + i] = src[i];
		i++;
	}
	// Null-terminate jika masih ada ruang
	if (dlen + i < dstsize)
		dst[dlen + i] = '\0';
	return dlen + slen;
} 