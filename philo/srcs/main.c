#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "philo.h"
#include "utils.h"



static void	run_philosophers(t_args args)
{
	(void)args;
}

int	main(int argc, char *argv[])
{
	t_args	args;

	if (!is_valid_argc(argc))
	{
		printf("Error: invalid arguments.\n");
		return (EXIT_FAILURE);
	}
	set_args(argc, argv, &args);
	run_philosophers(args);
	return (EXIT_SUCCESS);
}
