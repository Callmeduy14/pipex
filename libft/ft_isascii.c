#include "libft.h"

// Mengecek apakah karakter c adalah karakter ASCII (0-127).
int ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return 1;
	return 0;
} 