#include "libft.h"

// Melakukan fungsi f pada setiap content node dalam linked list lst.
void ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!f)
		return;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
} 