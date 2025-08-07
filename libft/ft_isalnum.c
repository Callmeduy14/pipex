#include "libft.h"

// Mengecek apakah karakter c adalah alfanumerik (huruf atau angka).
int ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))
		return 1;
	return 0;
} 