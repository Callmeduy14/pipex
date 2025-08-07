#include "libft.h"

// Membuat node baru untuk linked list, mengisi content dan next = NULL.
t_list *ft_lstnew(void *content)
{
	t_list *node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return NULL;
	node->content = content;
	node->next = NULL;
	return node;
} 