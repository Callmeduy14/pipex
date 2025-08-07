#include "libft.h"

// Mengecek apakah karakter c adalah huruf alfabet (A-Z atau a-z).
int ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return 1;
	return 0;
} 