#include "philo.h"
#include "utils.h"

bool	is_valid_argc(const int argc)
{
	return (argc == 5 || argc == 6);
}

static void	init_t_args(t_args *args)
{
	args->num_of_philos = 0;
	args->time_to_die = 0;
	args->time_to_eat = 0;
	args->time_to_sleep = 0;
	args->num_of_times_each_philo_must_eat = 0;
	args->start_time = 0;
	args->philos = NULL;
	args->forks = NULL;
	args->is_any_philo_died = false;
}

static t_philo	**allocate_philos(const int num_of_philos)
{
	t_philo	**philos;

	philos = (t_philo **)malloc(sizeof(t_philo *) * num_of_philos);
	if (philos == NULL)
		return (NULL);
	return (philos);
}

// todo: change ft_atoi's type, check error
t_args	set_args(const int argc, const char **argv, t_result *result)
{
	t_args	args;

	init_t_args(&args);
	ft_atoi(argv[1], &args.num_of_philos);
	ft_atoi(argv[2], &args.time_to_die);
	ft_atoi(argv[3], &args.time_to_eat);
	ft_atoi(argv[4], &args.time_to_sleep);
	if (argc == 6)
		ft_atoi(argv[5], &args.num_of_times_each_philo_must_eat);
	args.philos = allocate_philos(args.num_of_philos);
	if (args.philos == NULL)
		*result = FAILURE;
	*result = SUCCESS;
	return (args);
}
