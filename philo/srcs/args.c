#include "philo.h"
#include "utils.h"

bool	is_valid_argc(const int argc)
{
	return (argc == 5 || argc == 6);
}

static void	init_t_args(t_args *args)
{
	args->number_of_philosophers = 0;
	args->time_to_die = 0;
	args->time_to_eat = 0;
	args->time_to_sleep = 0;
	args->number_of_times_each_philosopher_must_eat = 0;
}

// todo: change ft_atoi's type, check error
t_args	set_args(const int argc, const char **argv)
{
	t_args	args;

	init_t_args(&args);
	ft_atoi(argv[1], &args.number_of_philosophers);
	ft_atoi(argv[2], &args.time_to_die);
	ft_atoi(argv[3], &args.time_to_eat);
	ft_atoi(argv[4], &args.time_to_sleep);
	if (argc == 6)
		ft_atoi(argv[5], &args.number_of_times_each_philosopher_must_eat);
	return (args);
}
