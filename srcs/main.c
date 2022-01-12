#include "philo.h"
#include "simulation.h"
#include "error_message.h"

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
		(*philo_array)[i] = (t_philo){i + 1, 0, true, \
			data, PTHREAD_MUTEX_INIT, NULL};
		if (pthread_mutex_init(&(*philo_array)[i].left, NULL))
		{
			printf("%s%i\n", MUTEX_INIT, i + 1);
			return (1);
		}
		if (i)
			(*philo_array)[i - 1].right = &(*philo_array)[i].left;
	}
	(*philo_array)[i].right = &(*philo_array)[0].left;
	return (0);
}

static int	check_philosopher(t_data *data, t_philo **philo_array)
{
	(void)data;
	(void)philo_array;
	sleep(2);
	pthread_mutex_lock(&data->mutex);
	data->should_stop = true;
	pthread_mutex_unlock(&data->mutex);
	printf("Stopping...\n");
	return (1);
}

static int	wait_end_philo(t_data *data, t_philo **philo_array)
{
	(void)philo_array;
	while (1)
	{
		pthread_mutex_lock(&data->mutex);
		if (data->has_stop == data->args->nbp)
			break ;
		pthread_mutex_unlock(&data->mutex);
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
	for (int i = 0; i < args.nbp; i++)
		printf("nbr_philo : %zu nbr_lunch : %zu is_alive : %s\n", \
				philo_array[i].nbr_philo, philo_array[i].nbr_lunch, \
				philo_array[i].is_alive ? "true" : "false");
	data = (t_data){&args, {0, 0}, 0, false, 0, PTHREAD_MUTEX_INIT, NULL};
	start_simulation(&data, &philo_array);
	// check if each philo is fed
	check_philosopher(&data, &philo_array);
	wait_end_philo(&data, &philo_array);
	while (++i < args.nbp)
		pthread_mutex_destroy(&philo_array[i].left);
	free(data.tid);
	free(philo_array);
}
