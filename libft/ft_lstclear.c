#include "libft.h"

// Menghapus seluruh node dalam linked list lst dan membebaskan memori content dengan fungsi del.
void ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *tmp;
	if (!lst || !del)
		return;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
} 