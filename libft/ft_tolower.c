#include "libft.h"

// Mengubah huruf besar menjadi huruf kecil jika c adalah huruf besar.
int ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return c + 32;
	return c;
} 