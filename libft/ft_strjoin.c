#include "libft.h"

// Menggabungkan dua string s1 dan s2 ke dalam memori baru.
char *ft_strjoin(char const *s1, char const *s2)
{
	size_t len1 = 0;
	size_t len2 = 0;
	size_t i = 0;
	size_t j = 0;
	char *res;
	if (!s1 || !s2)
		return NULL;
	while (s1[len1])
		len1++;
	while (s2[len2])
		len2++;
	// Alokasi memori untuk hasil gabungan
	res = (char *)malloc(len1 + len2 + 1);
	if (!res)
		return NULL;
	// Salin s1 ke hasil
	while (i < len1)
	{
		res[i] = s1[i];
		i++;
	}
	// Salin s2 ke hasil
	while (j < len2)
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	return res;
} 