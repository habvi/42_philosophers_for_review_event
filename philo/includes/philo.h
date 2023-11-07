#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include "result.h"

# define MUTEX_SUCCESS	0
# define THREAD_SUCCESS	0
# define EXCEEDED 		1

# define MSG_FORK	"has taken a fork"
# define MSG_EAT	"is eating"
# define MSG_SLEEP	"is sleeping"
# define MSG_THINK	"is thinking"
# define MSG_DIED	"died"

# define ERR_INVALID_ARG	"Error: invalid arguments."
# define ERR_FATAL			"Error: fatal error."

typedef struct s_philo	t_philo;

typedef struct s_args {
	unsigned int	num_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	num_of_times_each_philo_must_eat;
	// common data
	int64_t			start_time;
	t_philo			**philos;
	pthread_mutex_t	shared;
	pthread_mutex_t	*forks;
	bool			is_any_philo_died;
	bool			is_error;
}	t_args;

typedef struct s_philo {
	unsigned int	id;
	t_args			*args;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	// not const
	int64_t			start_time_of_cycle;
}	t_philo;

typedef struct s_monitor {
	unsigned int	id;
	t_args			*args;
}	t_monitor;

/* args */
bool		is_valid_argc(const int argc);
t_args		set_args(const int argc, const char **argv, t_result *result);

/* destroy */
void		destroy_forks(pthread_mutex_t **forks, const unsigned int max_len);
void		destroy(t_args *args, pthread_t **philos, \
							pthread_t **monitors, const unsigned int max_len);
void		destroy_all(t_args *args, pthread_t **philos, pthread_t **monitors);

/* mutex */
int64_t		call_atomic(pthread_mutex_t *mutex, int64_t (*func)(), t_args *args);
t_result	init_mutex(t_args *args);

/* thread_create */
pthread_t	*simulate_philos_cycle(t_args *args);

/* philo_behaviors */
t_result	take_two_forks(t_philo *philo);
void		eating(t_philo *philo);
void		put_two_forks(const t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);

/* philo_cycle */
bool		is_any_philo_died(const t_philo *philo);
bool		is_any_philo_died_atomic(const t_philo *philo);
void		*philo_cycle(void *thread_args);

/* monitor*/
pthread_t	*monitoring_death(t_args *args, pthread_t **philo_threads);
void		*monitor_cycle(void *thread_args);

/* time */
void		set_start_time(t_args *args);
int64_t		get_elapsed_time(t_philo *philo);
int64_t		get_elapsed_cycle_time(const int64_t start_time_of_cycle);
void		set_start_time_of_cycle(t_philo *philo);
void		usleep_gradual(int64_t sleep_time, const t_philo *philo);

/* put */
void		put_log(t_philo *philo, const char *message, \
										int64_t (*get_time)(t_philo *philo));
t_result	fatal_error(void);

#endif
