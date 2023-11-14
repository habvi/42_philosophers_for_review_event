#include "ft_deque.h"
#include <stdio.h>
#include <unistd.h>

void	deque_print(t_deque *deque)
{
	t_deque_node	*node;

	if (deque_is_empty(deque))
	{
		dprintf(STDERR_FILENO, "deque is empty!\n");
		dprintf(STDERR_FILENO, "---------------------\n");
		return ;
	}
	dprintf(STDERR_FILENO, "cotent: ");
	node = deque->node;
	while (node)
	{
		dprintf(STDERR_FILENO, "[%s]", (char *)node->content);
		node = node->next;
	}
	dprintf(STDERR_FILENO, "\nsize  : %zu\n", deque->size);
	dprintf(STDERR_FILENO, "---------------------\n");
}

void	debug_deque_print(t_deque *deque, const char *func_name)
{
	dprintf(STDERR_FILENO, ">>> %s\n", func_name);
	deque_print(deque);
}
