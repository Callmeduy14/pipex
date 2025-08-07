#include "libft.h"

// Fungsi pembantu: Menghitung jumlah kata yang dipisahkan oleh delimiter c
static size_t count_words(const char *s, char c)
{
	size_t count = 0;
	int in_word = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return count;
}

// Fungsi pembantu: Membebaskan seluruh array string jika terjadi error
static void free_all(char **arr, size_t n)
{
	size_t i = 0;
	while (i < n)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

// Memecah string s menjadi array string berdasarkan delimiter c.
// Setiap kata di-allocasi dengan malloc, hasil diakhiri NULL.
char **ft_split(char const *s, char c)
{
	size_t words, i = 0, j = 0, start = 0;
	char **arr;
	if (!s)
		return NULL;
	words = count_words(s, c);
	arr = (char **)malloc((words + 1) * sizeof(char *));
	if (!arr)
		return NULL;
	while (s[i] && j < words)
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		arr[j] = ft_substr(s, start, i - start);
		if (!arr[j])
		{
			free_all(arr, j);
			return NULL;
		}
		j++;
	}
	arr[j] = NULL;
	return arr;
} 