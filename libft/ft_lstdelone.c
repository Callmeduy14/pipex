#include "libft.h"

// Menghapus satu node lst dan membebaskan memori content dengan fungsi del.
void ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return;
	del(lst->content);
	free(lst);
} 