#include <stdio.h>
#include "philo.h"
#include "utils.h"

bool	is_valid_argc(const int argc)
{
	if (!(argc == 5 || argc == 6))
	{
		printf("%s\n", ERR_INVALID_ARG);
		return (false);
	}
	return (true);
}

static void	init_args(t_args *args)
{
	args->num_of_philos = 0;
	args->time_to_die = 0;
	args->time_to_eat = 0;
	args->time_to_sleep = 0;
	args->num_of_each_philo_must_eat = 0;
	args->start_time = 0;
	args->philos = NULL;
	args->forks = NULL;
	args->is_any_philo_died = false;
	args->is_thread_error = false;
	args->num_of_finish_eat = 0;
}

static t_result	set_argv(const int argc, const char **argv, t_args *args)
{
	bool	is_correct_num;

	is_correct_num = true;
	is_correct_num &= ft_atoi(argv[1], &args->num_of_philos);
	is_correct_num &= ft_atoi(argv[2], &args->time_to_die);
	is_correct_num &= ft_atoi(argv[3], &args->time_to_eat);
	is_correct_num &= ft_atoi(argv[4], &args->time_to_sleep);
	if (argc == 6)
		is_correct_num &= ft_atoi(argv[5], &args->num_of_each_philo_must_eat);
	if (!is_correct_num)
		return (FAILURE);
	return (SUCCESS);
}

static t_philo	*allocate_philos(const unsigned int num_of_philos)
{
	t_philo	*philos;

	philos = (t_philo *)malloc(sizeof(t_philo) * num_of_philos);
	if (philos == NULL)
		return (NULL);
	return (philos);
}

t_args	set_args(const int argc, const char **argv, t_result *result)
{
	t_args	args;

	*result = SUCCESS;
	init_args(&args);
	*result = set_argv(argc, argv, &args);
	if (*result == FAILURE)
	{
		printf("%s\n", ERR_INVALID_ARG);
		return (args);
	}
	args.philos = allocate_philos(args.num_of_philos);
	if (args.philos == NULL)
		*result = FAILURE;
	return (args);
}
