#include "libft.h"

// Mengembalikan pointer ke node terakhir dalam linked list lst.
t_list *ft_lstlast(t_list *lst)
{
	if (!lst)
		return NULL;
	while (lst->next)
		lst = lst->next;
	return lst;
} 