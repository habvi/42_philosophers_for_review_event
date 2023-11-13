#ifndef UTILS_H
# define UTILS_H

# include "result.h"
# include <stdbool.h>

typedef struct s_args	t_args;
typedef struct s_philo	t_philo;

/* utils */
int64_t		call_atomic(pthread_mutex_t *mutex, int64_t (*func)(), void *args);
bool		ft_atoi_positive(const char *str, unsigned int *num);
void		*ft_free(void **ptr);
bool		ft_isdigit(int c);
int64_t		get_current_time_usec(void);
int64_t		get_current_time_msec(void);

/* debug */
void		put_args(const t_args *args);
void		put(const t_philo *philo, char *message);

#endif
