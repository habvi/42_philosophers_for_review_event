#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include "result.h"

# define MUTEX_SUCCESS	0
# define THREAD_SUCCESS	0

# define MAX_DURATION		500000
# define MONITOR_DURATION	500
# define NOT_SET			(-1)

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

# ifdef COLOR
#  define RED	"\033[31m"
#  define GREEN	"\033[32m"
#  define BLUE	"\033[34m"
#  define PINK	"\033[35m"
#  define END	"\033[0m"
# else
#  define RED
#  define GREEN
#  define BLUE
#  define PINK
#  define END
# endif

typedef struct s_philo		t_philo;
typedef struct s_deque		t_deque;
typedef struct s_deque_node	t_deque_node;

typedef struct s_args {
	unsigned int	num_of_philos;
	int64_t			time_to_die;
	int64_t			time_to_eat;
	int64_t			time_to_sleep;
	int64_t			time_to_think;
	int64_t			num_of_each_philo_must_eat;
}	t_args;

typedef struct s_shared {
	pthread_mutex_t	shared;
	int64_t			start_time;
	bool			is_any_philo_dead;
	bool			is_thread_error;
	unsigned int	num_of_finish_eat;
}	t_shared;

typedef struct s_philo {
	unsigned int	id;
	t_args			args;
	t_shared		*shared;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
	int64_t			start_time_of_philo;
	int64_t			start_time_of_cycle;
	unsigned int	eat_count;
	bool			is_self_dead;
	int64_t			current_time;
}	t_philo;

/* args */
bool			is_valid_argc(const int argc);
t_args			set_args(const int argc, const char **argv, t_result *result);

/* init */
t_philo			*init_philos(\
					t_args *args, t_shared *shared, pthread_mutex_t **forks);

/* destroy */
void			destroy_philos(t_philo **philos, \
									t_shared *shared, pthread_mutex_t **forks);
void			destroy_mutex(t_shared *shared, \
					pthread_mutex_t **forks, const unsigned int num_of_philos);
void			destroy_forks(\
						pthread_mutex_t **forks, const unsigned int max_len);
void			destroy_threads(t_deque **threads);

/* thread */
t_result		add_threads_list(t_deque *threads, pthread_t new_thread);
t_deque_node	*create_thread_node(pthread_t new_thread);
bool			wait_start(t_philo *philo);

/* philo_action */
int64_t			is_simulation_over(t_philo *philo);
bool			is_simulation_over_atomic(t_philo *philo);
int64_t			philo_action(t_philo *philo, int64_t (*action)(t_philo *));

/* philo_simulate */
t_result		simulate_philos_cycle(t_philo *philos, \
							t_shared *shared, const unsigned int num_of_philos);

/* philo_cycle */
void			*philo_solo_cycle(void *thread_args);
void			*philo_cycle(void *thread_args);

/* philo_behaviors */
void			take_fork(pthread_mutex_t *fork, t_philo *philo);
void			take_two_forks(t_philo *philo);
void			eating(t_philo *philo);
void			put_fork(pthread_mutex_t *fork);
void			put_two_forks(t_philo *philo);
void			sleeping(t_philo *philo);
void			thinking(t_philo *philo);

/* monitor_cycle */
void			*monitor_cycle(void *thread_args);

/* put */
void			put_log(const t_philo *philo, const char *message);
int64_t			put_log_flow(\
					t_philo *philo, void (*set_time)(), const char *message);
void			error_args(void);
t_result		error_fatal(void);

/* usleep */
void			usleep_gradual(int64_t sleep_time, t_philo *philo);

#endif
