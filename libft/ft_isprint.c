#include "libft.h"

// Mengecek apakah karakter c adalah karakter yang bisa dicetak (spasi sampai ~).
int ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return 1;
	return 0;
} 