#include "libft.h"

// Membuat duplikasi string s1 ke memori baru (menggunakan malloc).
char *ft_strdup(const char *s1)
{
	size_t len = 0;
	char *dup;
	while (s1[len])
		len++;
	// Alokasi memori untuk string baru
	dup = (char *)malloc(len + 1);
	if (!dup)
		return NULL;
	// Salin karakter satu per satu
	for (size_t i = 0; i <= len; i++)
		dup[i] = s1[i];
	return dup;
} 