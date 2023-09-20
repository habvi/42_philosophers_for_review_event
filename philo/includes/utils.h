#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>

typedef struct s_args  t_args;

/* utils */
bool	ft_atoi(const char *str, int *num);
bool	ft_isdigit(int c);

/* debug */
void	put_args(t_args *args);

#endif
