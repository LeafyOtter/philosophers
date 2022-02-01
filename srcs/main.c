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
		(*philo_array)[i] = (t_philo){i + 1, 0, {0, 0}, true, false,
			PTHREAD_MUTEX_INIT, data, PTHREAD_MUTEX_INIT, NULL};
		if (pthread_mutex_init(&(*philo_array)[i].left, NULL))
			return (printf("%s%i\n", MUTEX_INIT, i + 1));
		if (pthread_mutex_init(&(*philo_array)[i].mutex, NULL))
			return (printf("%s%i\n", MUTEX_INIT, i + 1));
		if (i)
			(*philo_array)[i - 1].right = &(*philo_array)[i].left;
	}
	(*philo_array)[nbp - 1].right = &(*philo_array)[0].left;
	return (0);
}

static int	check_philosopher(t_data *data, t_philo *philo_array)
{
	size_t		i;
	t_timeval	time;
	long		time_ms;

	i = 0;
	while (!data->should_stop)
	{
		if (i == data->args->nbp)
			i = 0;
		gettimeofday(&time, NULL);
		pthread_mutex_lock(&(philo_array)[i].mutex);
		time_ms = ((time.tv_sec - (philo_array)[i].last_lunch.tv_sec) * 1000) \
			+ ((time.tv_usec - (philo_array)[i].last_lunch.tv_usec) / 1000);
		pthread_mutex_lock(&data->mutex);
//		printf("blabla debug: %zu\n", (philo_array)[i].nbr_lunch);
		if (((philo_array)[i].nbr_lunch == data->args->ntpme) && \
			!(philo_array)[i].lunch)
		{
			data->nbr_philo_fed++;
			(philo_array)[i].lunch = true;
//			printf("i am the culpright\n");
		}
		if (time_ms * 1000 > data->args->ttd)
		{
			(philo_array)[i].is_alive = false;
			data->should_stop = true;
//			printf("liar it is me\n");
		}
		if (data->nbr_philo_fed == data->args->nbp)
		{
			data->should_stop = true;
//			printf("nononono its me\n");
		}
		pthread_mutex_unlock(&data->mutex);
		pthread_mutex_unlock(&(philo_array)[i].mutex);
		i++;
	}
	return (1);
}

static int	wait_end_philo(t_data *data)
{
	size_t	tmp;

	while (1)
	{
		pthread_mutex_lock(&data->mutex);
		tmp = data->has_stop;
		pthread_mutex_unlock(&data->mutex);
		if (tmp == data->args->nbp)
			break ;
	}
	return (0);
}

// check if each philo is fed

int	main(int ac, char **av)
{
	size_t			i;
	t_args			args;
	t_data			data;
	t_philo			*philo_array;

	i = 0;
	args = (t_args){0, 0, 0, 0, 0};
	if (parsing(ac, av, &args))
		return (1);
	if (create_philosophers(&data, args.nbp, &philo_array))
		return (1);
	data = (t_data){&args, {0, 0}, 0, false, 0, PTHREAD_MUTEX_INIT, NULL};
	start_simulation(&data, &philo_array);
	check_philosopher(&data, philo_array);
	wait_end_philo(&data);
	while (i < args.nbp)
	{
	//	printf("NUMBER OF TIME %zu ATE : %zu\n", (philo_array)[i].nbr_philo, (philo_array)[i].nbr_lunch);
		pthread_mutex_destroy(&philo_array[i].left);
		i++;
	}
	free(data.tid);
	free(philo_array);
}

/*
 * 	for (int i = 0; i < args.nbp; i++)
 *		printf("nbr_philo : %zu nbr_lunch : %zu is_alive : %s\n", 
 *				philo_array[i].nbr_philo, philo_array[i].nbr_lunch, 
 *				philo_array[i].is_alive ? "true" : "false");
 */