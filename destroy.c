/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:03:25 by yalkhidi          #+#    #+#             */
/*   Updated: 2025/10/02 13:27:27 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_all_dead(t_input *input)
{
	unsigned int	i;

	i = -1;
	while (++i < input->n_philo)
	{
		pthread_mutex_lock(&input->philos[i].dead_lock);
		input->philos[i].dead = 1;
		pthread_mutex_unlock(&input->philos[i].dead_lock);
	}
}

void	status_log(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->input->write_lock);
	if (philo->input->finished == 0)
		printf("%ld %u %s\n", get_time() - philo->start_time, philo->id, status);
	pthread_mutex_unlock(&philo->input->write_lock);
}

void	clean(t_input *input, char *message)
{
	int	i;

	if (input->forks)
	{
		i = -1;
		while (++i < (int)input->n_philo)
			pthread_mutex_destroy(&input->forks[i]);
		free(input->forks);
	}
	if (input->philos)
	{
		i = -1;
		while (++i < (int)input->n_philo)
		{
			pthread_mutex_destroy(&input->philos[i].meal_lock);
			pthread_mutex_destroy(&input->philos[i].dead_lock);
		}
		free(input->philos);
	}
	pthread_mutex_destroy(&input->write_lock);
	if (input)
		free(input);
	if (message)
		print_message(message);
}
