#include "libft.h"

// Membandingkan dua string s1 dan s2 hingga n karakter.
// Mengembalikan selisih karakter pertama yang berbeda, atau 0 jika sama.
int ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0)
	{
		if (*s1 != *s2 || *s1 == '\0' || *s2 == '\0')
			return (unsigned char)*s1 - (unsigned char)*s2;
		s1++;
		s2++;
		n--;
	}
	return 0;
} 