#include "libft.h"

// Menulis representasi angka n ke file descriptor fd.
void ft_putnbr_fd(int n, int fd)
{
	long num = n;
	char c;
	// Tangani angka negatif
	if (num < 0)
	{
		write(fd, "-", 1);
		num = -num;
	}
	// Rekursif untuk digit sebelum digit terakhir
	if (num >= 10)
		ft_putnbr_fd(num / 10, fd);
	// Tulis digit terakhir
	c = (char)(num % 10 + '0');
	write(fd, &c, 1);
} 