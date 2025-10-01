/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:19:56 by yalkhidi          #+#    #+#             */
/*   Updated: 2025/10/01 17:42:20 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long   get_time(void)
{
    struct timeval time;
    unsigned long time_in_ms;

    gettimeofday(&time, NULL);
    time_in_ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    return (time_in_ms);
}

void    init(t_input *input)
{
    int i;

    input->philos = malloc(sizeof(t_philo) * input->n_philo);
    if (!input->philos)
        clean(input, "Error\nCouldn't allocate philosophers\n");
    input->forks = malloc(sizeof(pthread_mutex_t) * input->n_philo);
    if (!input->forks)
        clean(input, "Error\nCouldn't allocate forks\n");
    i = 0;
    while (i < (int)input->n_philo)
    {
        if (pthread_mutex_init(&input->forks[i], NULL) != 0)
            clean(input, "Error\nCouldn't initiate fork mutex\n");
        if (pthread_mutex_init(&input->philos[i].meal_lock, NULL) != 0)
            clean(input, "Error\nCouldn't initiate meal mutex\n");
        if (pthread_mutex_init(&input->philos[i].write_lock, NULL) != 0)
            clean(input, "Error\nCouldn't initiate write mutex\n");
        if (pthread_mutex_init(&input->philos[i].dead_lock, NULL) != 0)
            clean(input, "Error\nCouldn't initiate dead mutex\n");
        i++;
    }
    assign_philos(input);
}

void    assign_philos(t_input *input)
{
    int i;

    i = 0;
    while(i < (int)input->n_philo)
    {
        input->philos[i].id = (unsigned int)i + 1;
        input->philos[i].r_fork = i;
        input->philos[i].l_fork = ((i + input->n_philo - 1) % input->n_philo);
        input->philos[i].start_time = get_time();
        input->philos[i].meals_ate = 0;
        input->philos[i].last_meal= 0;
        input->philos[i].eating = 0;
        input->philos[i].dead = 0;
        input->philos[i].input = input;
        i++;
    }
    create_threads(input);
}

void    create_threads(t_input *input)
{
    int i;
    pthread_t   waiter;

    if (pthread_create(&waiter, NULL, moniter, (void *)input) != 0)
        clean(input, "Error\nCouldn't create thread\n");
    i = -1;
    while (++i < (int)input->n_philo)
    {
        if (pthread_create(&input->philos[i].thread, NULL, routine, (void *)&input->philos[i]) != 0)
            clean(input, "Error\nCouldn't create thread\n");
    }
    if (pthread_join(waiter, NULL) != 0)
        clean(input, "Error\nCouldn't join thread\n");
    i = -1;
    while (++i < (int)input->n_philo)
    {
        if (pthread_join(input->philos[i].thread, NULL) != 0)
            clean(input, "Error\nCouldn't join thread\n");
    }
}
 