#include <stdlib.h>
#include <stdio.h>

typedef struct s_list
{
	struct	s_list	*next;
	int				value;
}	t_list;

// append value to list
void	list_append(t_list **list, int value)
{
	t_list	*new;
	t_list	*p;

	// malloc list element
	new = malloc(sizeof(t_list));
	new->value = value;
	new->next = NULL;

	// if pointer to first element is NULL, new element is first element of list
	if (*list == NULL)
	{
		*list = new;
		return ;
	}

	// append
	for (p = *list; p->next != NULL; p = p->next);
	p->next = new;
}

int	main(void)
{
	t_list	*list;
	t_list	*p;
	int		i;

	list = NULL;

	// append value (1 ~ 100)
	for (i=1; i < 101; i++)
		list_append(&list, i);

	// print list values
	for (p = list; p != NULL; p = p->next)
	{
		if (p != list) printf(" ");
		printf("%d", p->value);
	}
}
