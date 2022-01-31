#include "philo.h"
#include "simulation.h"
#include "error_message.h"

/*
 *	void	dump_log(t_philo *philo)
 *	{
 *		printf("DEBUG THREAD: %li\n", philo->nbr_philo);
 *	}
 */

bool	check_death(t_data *data)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(&data->mutex);
	if (data->should_stop)
		ret = true;
	pthread_mutex_unlock(&data->mutex);
	return (ret);
}

void	print_status(t_philo *philo, char *str)
{
	t_timeval	time;
	t_timeval	time_stamp;
	long		time_ms;

	gettimeofday(&time, NULL);
	time_stamp.tv_sec = time.tv_sec - philo->data->start_sim.tv_sec;
	time_stamp.tv_usec = time.tv_usec - philo->data->start_sim.tv_usec;
	time_ms = (time_stamp.tv_sec * 1000) + (time_stamp.tv_usec / 1000);
	printf("%li %zu %s\n", time_ms, philo->nbr_philo, str);
}

// TODO: stock time of lunch in struct
// TODO: segment usleep()

bool	philo_usleep(t_philo *philo, suseconds_t time_to_wait)
{
	suseconds_t	waited_time;

	waited_time = 0;
	while (1)
	{
		if (time_to_wait <= waited_time)
			break ;
		usleep(WAIT_TIME);
		if (check_death(philo->data))
			return (true);
		waited_time += WAIT_TIME;
	}
	if (waited_time < time_to_wait)
		usleep(time_to_wait - waited_time);
	if (check_death(philo->data))
		return (true);
	return (false);
}

int	start_simulation(t_data *data, t_philo **philo_array)
{
	int	i;

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
		(*philo_array)[i].last_lunch = data->start_sim;
		pthread_create(&(data->tid[i]), NULL, &routine, &(*philo_array)[i]);
		pthread_detach(data->tid[i]);
		i++;
	}
	return (1);
}
