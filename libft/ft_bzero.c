#include "libft.h"

// Fungsi ini mengisi blok memori dengan nol (0) sebanyak n byte.
void ft_bzero(void *s, size_t n)
{
	// Memanfaatkan ft_memset untuk mengisi dengan 0
	ft_memset(s, 0, n);
} 