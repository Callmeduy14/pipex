#include "libft.h"

// Membuat linked list baru hasil transformasi setiap content node lst dengan fungsi f.
// Jika terjadi error, seluruh node yang sudah dialokasi akan dibebaskan dengan del.
t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *newlst = NULL;
	t_list *newnode;
	void *content;
	if (!f || !del)
		return NULL;
	while (lst)
	{
		content = f(lst->content);
		newnode = ft_lstnew(content);
		if (!newnode)
		{
			ft_lstclear(&newlst, del);
			return NULL;
		}
		ft_lstadd_back(&newlst, newnode);
		lst = lst->next;
	}
	return newlst;
} 