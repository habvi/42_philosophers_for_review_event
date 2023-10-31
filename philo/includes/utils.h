#ifndef UTILS_H
# define UTILS_H

# include "result.h"
# include <stdbool.h>

typedef struct s_args		t_args;
typedef struct s_philo		t_philo;
typedef struct s_philo_var	t_philo_var;

/* utils */
bool		ft_atoi(const char *str, int *num);
void		*ft_free(void **ptr);
bool		ft_isdigit(int c);
int64_t		get_current_time_usec(void);
int64_t		get_current_time_msec(void);

/* debug */
void		put_args(const t_args *args);
void		put(const t_philo *philo, const char *message);

#endif
