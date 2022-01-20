#include "philo.h"
#include "simulation.h"
#include "error_message.h"

void	dump_log(t_philo *philo)
{
	printf("DEBUG: %li\n", philo->nbr_philo);
}

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
	printf("%5li %zu %s\n", time_ms, philo->nbr_philo, str);
}

void	multi_mutex_unlock(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left);
	pthread_mutex_unlock(philo->right);
}

bool	eat_routine(t_philo *philo)
{
	if (philo->nbr_philo % 2)
	{
		pthread_mutex_lock(&philo->left);
		if (check_death(philo->data))
			return (pthread_mutex_unlock(&philo->left), true);
		print_status(philo, FORK_MSG);
		pthread_mutex_lock(philo->right);
		if (check_death(philo->data))
			return (multi_mutex_unlock(philo), true);
		print_status(philo, FORK_MSG);
	}
	else
	{
		pthread_mutex_lock(philo->right);
		if (check_death(philo->data))
			return (pthread_mutex_unlock(philo->right), true);
		print_status(philo, FORK_MSG);
		pthread_mutex_lock(&philo->left);
		if (check_death(philo->data))
			return (multi_mutex_unlock(philo), true);
		print_status(philo, FORK_MSG);
	}
	print_status(philo, EATING_MSG);
	usleep(philo->data->args->tte * 1000);
	return (multi_mutex_unlock(philo), false);
}

bool	sleep_routine(t_philo *philo)
{
	(void)philo;
	return (false);
}

void	*routine(void *arg)
{
	bool	break_flag;
	t_philo	*philo;

	philo = (t_philo *)arg;
	break_flag = false;
	while (!break_flag)
	{
		if (eat_routine(philo))
			break ;
		if (check_death(philo->data))
			break ;
		if (sleep_routine(philo))
			break ;
		if (check_death(philo->data))
			break ;
		print_status(philo, THINKING_MSG);
		usleep(25000);
		break_flag = check_death(philo->data);
	}
	pthread_mutex_lock(&philo->data->mutex);
	philo->data->has_stop++;
	pthread_mutex_unlock(&philo->data->mutex);
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
		pthread_detach(data->tid[i]);
		i++;
	}
	return (1);
}
