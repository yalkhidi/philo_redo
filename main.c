#include "philo.h"

void	print_inputs(t_input *inputs)
{
	printf("number of philos: %ld\n", inputs->n_philo);
	printf("time to die: %ld\n", inputs->t_die);
	printf("time to eat: %ld\n", inputs->t_eat);
	printf("time to sleep: %ld\n", inputs->t_sleep);
	printf("number of time each philo must eat: %ld\n", inputs->n_t_philo_eat);
}

int main(int ac, char **av)
{
    unsigned long *array;
    t_input *input;

    array = get_input(ac, av);
    if (array)
    {
        input = assign_inputs(array);
        init(input);
        if (input)
            free(input);
    }    
}
