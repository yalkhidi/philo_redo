/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:04:36 by yalkhidi          #+#    #+#             */
/*   Updated: 2025/10/02 13:14:45 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	unsigned long	*array;
	t_input			*input;

	array = get_input(ac, av);
	if (array)
	{
		input = assign_inputs(array);
		init(input);
		clean(input, NULL);
	}
}
