#include "libft.h"

// Mengubah huruf kecil menjadi huruf besar jika c adalah huruf kecil.
int ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return c - 32;
	return c;
} 