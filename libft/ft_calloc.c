#include "libft.h"

// Mengalokasikan memori untuk array sebanyak count elemen, setiap elemen berukuran size.
// Seluruh memori diinisialisasi dengan nol.
void *ft_calloc(size_t count, size_t size)
{
	void *ptr;
	ptr = malloc(count * size);
	if (!ptr)
		return NULL;
	// Inisialisasi seluruh memori dengan nol
	ft_bzero(ptr, count * size);
	return ptr;
} 