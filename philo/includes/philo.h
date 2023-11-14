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

# if defined(__linux__)
#  define SPEC_I64	"%ld"
# else
#  define SPEC_I64	"%lld"
# endif

typedef struct s_philo	t_philo;

typedef struct s_args {
	unsigned int	num_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	num_of_each_philo_must_eat;
	// common data
	int64_t			start_time;
	t_philo			*philos;
	pthread_mutex_t	shared;
	pthread_mutex_t	*forks;
	bool			is_any_philo_dead;
	bool			is_thread_error;
	unsigned int	num_of_finish_eat;
}	t_args;

typedef struct s_philo {
	unsigned int	id;
	t_args			*args;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	// not const
	int64_t			start_time_of_cycle;
	unsigned int	eat_count;
	bool			is_self_dead;
	int64_t			current_time;
}	t_philo;

typedef struct s_monitor {
	unsigned int	id;
	t_args			*args;
}	t_monitor;

/* args */
bool		is_valid_argc(const int argc);
t_args		set_args(const int argc, const char **argv, t_result *result);

/* destroy */
void		destroy_threads(\
				t_args *args, pthread_t **philos, const unsigned int max_len);
void		destroy_args(t_args *args);
void		destroy(t_args *args, pthread_t **philos, \
							pthread_t **monitors, const unsigned int max_len);

/* mutex */
t_result	init_mutex(t_args *args);
void		destroy_mutex(t_args *args);

/* philo_action */
int64_t		is_simulation_over(t_philo *philo);
bool		is_simulation_over_atomic(t_philo *philo);
int64_t		philo_action(t_philo *philo, int64_t (*action)(t_philo *));

/* philo_cycle */
void		*philo_solo_cycle(void *thread_args);
void		*philo_cycle(void *thread_args);

/* philo_behaviors */
void		take_fork(pthread_mutex_t *fork, t_philo *philo);
void		take_two_forks(t_philo *philo);
void		eating(t_philo *philo);
void		put_fork(pthread_mutex_t *fork);
void		put_two_forks(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);

/* philo_simulate */
pthread_t	*simulate_philos_cycle(t_args *args);

/* monitor*/
pthread_t	*monitoring_death(t_args *args, pthread_t **philo_threads);
void		*monitor_cycle(void *thread_args);

/* put */
void		put_log(const t_philo *philo, const char *message);
int64_t		put_log_flow(\
					t_philo *philo, void (*set_time)(), const char *message);
t_result	fatal_error(void);

/* usleep */
void		usleep_gradual(int64_t sleep_time, t_philo *philo);

#endif
