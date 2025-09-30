#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_input
{
	unsigned long	n_philo;
	unsigned long	t_die;
	unsigned long	t_eat;
	long			t_think;
	unsigned long	t_sleep;
	unsigned long	n_t_philo_eat;
	unsigned long	finished;
	pthread_mutex_t	*forks;
}	t_input;


unsigned long   ft_atoi(const char *str);
bool    ft_isdigit(char d);
bool is_within_limits(unsigned long num);
void    print_message(char *message);
int	words_count(char const *s);
char	**ft_split(char const *s);
void	free_split(char **split);
bool    check_valid_chars(char **str);
bool	check_valid_operators(int ac, char **av);
unsigned long *get_input(int ac, char **av);
t_input *assign_inputs(unsigned long *input_array);
#endif