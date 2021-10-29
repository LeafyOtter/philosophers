#include "main_philo.h"

static int	create_philosophers(t_data *data, int nbp, t_philo **philo_array)
{
	int	i;

	i = -1;
	(*philo_array) = (t_philo *)malloc(sizeof(t_philo) * nbp);
	if (!(*philo_array))
	{
		printf("%s\n", MALLOC_ERR);
		return (1);
	}
	while (++i < nbp)
	{
		(*philo_array)[i] = (t_philo){i + 1, 0, true, data, PTHREAD_MUTEX_INIT};
		if (pthread_mutex_init(&(*philo_array)[i].lock, NULL))
		{
			printf("%s%i\n", MUTEX_INIT, i + 1);
			return (1);
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	int				i;
	t_args			args;
	t_data			data;
	t_philo			*philo_array;

	i = 0;
	args = (t_args){0, 0, 0, 0, 0};
	if (parsing(ac, av, &args))
		return (1);
	if (create_philosophers(&data, args.nbp, &philo_array))
		return (1);
//	for (int i = 0; i < timep.nbp; i++)
//		printf("nbr_philo : %zu nbr_lunch : %zu is_alive : %s\n", \
//				philo_array[i].nbr_philo, philo_array[i].nbr_lunch, \
//				philo_array[i].is_alive ? "true" : "false");
	data.args = &args;
	data.should_stop = false;
	start_simulation(&data, &philo_array);
	while (++i < args.nbp)
		pthread_mutex_destroy(&philo_array[i].lock);
	free(philo_array);
}
