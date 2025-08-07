#include "libft.h"

// Menghitung jumlah node dalam linked list lst.
int ft_lstsize(t_list *lst)
{
	int count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return count;
} 