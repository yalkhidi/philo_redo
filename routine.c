/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:54:12 by yalkhidi          #+#    #+#             */
/*   Updated: 2025/10/02 13:39:47 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->dead_lock);
	if (philo->dead == 1 || philo->input->finished == 1)
	{
		pthread_mutex_unlock(&philo->dead_lock);
		set_all_dead(philo->input);
		return (0);
	}
	pthread_mutex_unlock(&philo->dead_lock);
	return (1);
}

void smart_usleep(t_input *input, unsigned long time_in_ms)
{
	unsigned long start = get_time();
	while (!input->finished)
	{
		if ((get_time() - start) >= time_in_ms)
			break;
		usleep(500); // sleep in very small chunks
	}
}

void	sleep_think(t_philo *philo)
{
	status_log(philo, "is sleeping");
	smart_usleep(philo->input, philo->input->t_sleep);
	status_log(philo, "is thinking");
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (alive(philo))
	{
		pthread_mutex_lock(&philo->input->forks[philo->r_fork]);
		status_log(philo, "has taken a fork");
		if (philo->input->n_philo == 1)
		{
			usleep(philo->input->t_die * 1000);
			pthread_mutex_unlock(&philo->input->forks[philo->r_fork]);
			return (arg);
		}
		pthread_mutex_lock(&philo->input->forks[philo->l_fork]);
		status_log(philo, "has taken a fork");
		status_log(philo, "is eating");
		pthread_mutex_lock(&philo->meal_lock);
		philo->eating = 1;
		philo->last_meal = get_time();
		philo->meals_ate++;
		// usleep(philo->input->t_eat * 1000);
		smart_usleep(philo->input, philo->input->t_eat);
		philo->eating = 0;
		pthread_mutex_unlock(&philo->meal_lock);
		pthread_mutex_unlock(&philo->input->forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->input->forks[philo->r_fork]);
		sleep_think(philo);
	}
	return (arg);
}
