#include "libft.h"

// Mengubah string menjadi integer (mirip atoi pada C).
// Mengabaikan whitespace, menangani tanda + dan -.
int ft_atoi(const char *str)
{
	int sign = 1;
	int result = 0;

	// Lewati whitespace
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	// Cek tanda + atau -
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	// Proses digit
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return result * sign;
} 