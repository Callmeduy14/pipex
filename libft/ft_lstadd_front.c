#include "libft.h"

// Menambahkan node baru (new) di depan linked list lst.
void ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return;
	new->next = *lst;
	*lst = new;
} 