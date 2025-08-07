#include "libft.h"

// Fungsi pembantu: Mengecek apakah karakter c ada di dalam string set
static int is_in_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return 1;
		set++;
	}
	return 0;
}

// Menghapus karakter di awal dan akhir string s1 yang ada di set, hasil di memori baru.
char *ft_strtrim(char const *s1, char const *set)
{
	size_t start = 0;
	size_t end;
	char *res;
	if (!s1 || !set)
		return NULL;
	end = 0;
	while (s1[end])
		end++;
	if (end == 0)
		return (char *)ft_calloc(1, 1);
	end--;
	// Cari indeks awal yang bukan bagian dari set
	while (s1[start] && is_in_set(s1[start], set))
		start++;
	// Cari indeks akhir yang bukan bagian dari set
	while (end > start && is_in_set(s1[end], set))
		end--;
	// Ambil substring hasil trim
	res = ft_substr(s1, start, end - start + 1);
	return res;
} 