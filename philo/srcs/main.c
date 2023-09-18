#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "philo.h"
#include "utils.h"

static bool	is_valid_argc(int argc)
{
	return (argc >= 5);
}

// todo: change type, check error
static void	set_args(int argc, char *argv[], t_args *args)
{
	ft_atoi(argv[1], &args->number_of_philosophers);
	ft_atoi(argv[2], &args->time_to_die);
	ft_atoi(argv[3], &args->time_to_eat);
	ft_atoi(argv[4], &args->time_to_sleep);
	printf("\nnum of philo  : %d\n", args->number_of_philosophers);
	printf("time to die   : %d\n", args->time_to_die);
	printf("time to eat   : %d\n", args->time_to_eat);
	printf("time to sleep : %d\n", args->time_to_sleep);
	if (argc == 6)
	{
		ft_atoi(argv[5], &args->number_of_times_each_philosopher_must_eat);
		printf("each philo must eat : %d\n", args->number_of_times_each_philosopher_must_eat);
	}
	printf("\n");
}

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
