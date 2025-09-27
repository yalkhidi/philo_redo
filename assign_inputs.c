/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:57:07 by yalkhidi          #+#    #+#             */
/*   Updated: 2025/09/27 17:41:29 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	split_arg(char **arg, unsigned long *in_array, int *in_ptr)
{
	char **splitted;
	int	j;
	int in;

	j = 0;
	in = *in_ptr;
	splitted = ft_split(arg);
	while (splitted[j])
	{
		in_array[in] = ft_atoi(splitted[j]);
		if (!is_within_limits(in_array[in]))
			return(free_split(splitted), free(in_array), false);
		in++;
		j++;
	}
	in_ptr = in;
	free_split(splitted);
	return (true);
}

