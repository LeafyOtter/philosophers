#include "simulation_philo.h"
#include <unistd.h>

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;

	printf("Philo number %zu reporting for duty\n", philo->nbr_philo);
	return (NULL);
}

int start_simulation(t_data *data, t_philo **philo_array)
{
	int i;

	i = 0;
	gettimeofday(&data->start_sim, NULL);
	data->tid = (pthread_t *)malloc(sizeof(pthread_t) * data->args->nbp);
	if (!data->tid)
	{
		printf("%s\n", MALLOC_ERR);
		return (1);
	}
	while (i < data->args->nbp)
	{
		(*philo_array)[i].data = data;
		pthread_create(&(data->tid[i]), NULL, &routine, &(*philo_array)[i]);
		i++;
	}
	sleep(2);
	return (1);
}
