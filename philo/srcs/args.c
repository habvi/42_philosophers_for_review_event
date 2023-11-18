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
	args->time_to_think = 0;
	args->num_of_each_philo_must_eat = 0;
}

static t_result	set_argv(const int argc, const char **argv, t_args *args)
{
	bool	is_correct_num;

	is_correct_num = true;
	is_correct_num &= ft_atoi_positive_uint(argv[1], &args->num_of_philos);
	is_correct_num &= (args->num_of_philos >= 1);
	is_correct_num &= ft_atoi_positive_int64(argv[2], &args->time_to_die);
	is_correct_num &= ft_atoi_positive_int64(argv[3], &args->time_to_eat);
	is_correct_num &= ft_atoi_positive_int64(argv[4], &args->time_to_sleep);
	if (argc == 6)
		is_correct_num &= ft_atoi_positive_uint(\
									argv[5], &args->num_of_each_philo_must_eat);
	if (!is_correct_num)
		return (FAILURE);
	args->time_to_die *= 1000;
	args->time_to_eat *= 1000;
	args->time_to_sleep *= 1000;
	args->time_to_think = calc_time_to_think(args);
	return (SUCCESS);
}

t_args	set_args(const int argc, const char **argv, t_result *result)
{
	t_args	args;

	init_args(&args);
	*result = set_argv(argc, argv, &args);
	if (*result == FAILURE)
		printf("%s\n", ERR_INVALID_ARG);
	return (args);
}
