/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:00:12 by yalkhidi          #+#    #+#             */
/*   Updated: 2025/10/02 13:09:05 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	if ((get_time() - philo->last_meal) > philo->input->t_die
		&& philo->eating == 0)
	{
		pthread_mutex_unlock(&philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_lock);
	return (0);
}

int	if_dead(t_input *input)
{
	int	i;

	i = -1;
	while (++i < (int)input->n_philo)
	{
		if (check_death(&input->philos[i]))
		{
			pthread_mutex_lock(&input->philos[i].dead_lock);
			if (!input->finished)
			{
				input->philos[i].dead = 1;
				input->finished = 1;
				// status_log(&input->philos[i], "is dead");
				printf("%ld %u died\n", get_time() - input->philos[i].start_time, input->philos[i].id);
			}
			pthread_mutex_unlock(&input->philos[i].dead_lock);
			return (1);
		}
	}
	return (0);
}

int	check_if_all_ate(t_input *input)
{
	int	i;
	int	meals;

	if (input->n_t_philo_eat > 0)
	{
		i = -1;
		meals = 0;
		while (++i < (int)input->n_philo)
		{
			pthread_mutex_lock(&input->philos[i].meal_lock);
			if (input->philos[i].meals_ate >= input->n_t_philo_eat)
				meals++;
			pthread_mutex_unlock(&input->philos[i].meal_lock);
		}
		if (meals == (int)input->n_philo)
		{
			set_all_dead(input);
			return (1);
		}
	}
	return (0);
}

void	*moniter(void *arg)
{
	t_input	*input;

	input = (t_input *)arg;
	while (1)
	{
		if (if_dead(input) || check_if_all_ate(input))
			break ;
		usleep(100);
	}
	return (arg);
}
