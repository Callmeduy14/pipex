#include "libft.h"

// Fungsi pembantu: Menghitung jumlah digit yang dibutuhkan untuk representasi string
static size_t ft_numlen(int n)
{
	size_t len = 0;
	long num = n;
	if (num <= 0)
	{
		len++;
		num = -num;
	}
	while (num > 0)
	{
		len++;
		num /= 10;
	}
	return len;
}

// Mengubah integer n menjadi string (menggunakan malloc untuk hasilnya)
char *ft_itoa(int n)
{
	long num = n;
	size_t len = ft_numlen(n);
	char *str = (char *)malloc(len + 1);
	if (!str)
		return NULL;
	str[len] = '\0';
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	if (num == 0)
		str[0] = '0';
	while (num > 0)
	{
		str[--len] = (num % 10) + '0';
		num /= 10;
	}
	return str;
} 