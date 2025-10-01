/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:54:12 by yalkhidi          #+#    #+#             */
/*   Updated: 2025/10/01 17:33:09 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
int    alive(t_philo *philo)
{
    pthread_mutex_lock(&philo->dead_lock);
    if (philo->dead == 1)
    {
        pthread_mutex_unlock(&philo->dead_lock);
        return (0);
    }
    pthread_mutex_unlock(&philo->dead_lock);
    return (1);
}

void    *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->id % 2 == 0)
    {
        usleep(1000);
    }
    while(alive(philo))
    {
        pthread_mutex_lock(&philo->input->forks[philo->r_fork]);
        status_log(*philo, "has taken a fork");
        pthread_mutex_lock(&philo->input->forks[philo->l_fork]);
        status_log(*philo, "has taken a fork");
        philo->eating = 1;
        status_log(*philo, "is eating");
        pthread_mutex_lock(&philo->meal_lock);
        philo->last_meal = get_time();
        philo->meals_ate++;
        printf("meals_eaten : %d\n", philo->meals_ate);
        pthread_mutex_unlock(&philo->meal_lock);
        usleep(philo->input->t_eat * 1000);
        philo->eating = 0;
        pthread_mutex_unlock(&philo->input->forks[philo->l_fork]);
        pthread_mutex_unlock(&philo->input->forks[philo->r_fork]);
        status_log(*philo, "is sleeping");
        usleep(philo->input->t_sleep * 1000);
        status_log(*philo, "is thinking");
    }
    return (arg);
}
