#include "philo.h"
#include "simulation.h"
#include "error_message.h"

bool	sleep_routine(t_philo *philo)
{
	print_status(philo, SLEEPING_MSG);
	if (philo_usleep(philo, philo->data->args->tts))
		return (true);
	return (false);
}

/*
			gettimeofday(&time, NULL);
			time_ms = ((time.tv_sec - philo->last_lunch.tv_sec) * 1000) \
				+ ((time.tv_usec - philo->last_lunch.tv_usec) / 1000);
			tmp = (philo->data->args->tte + philo->data->args->tts) >> 1;
//			dprintf(fd, "philo %zu : %li %li\n", philo->nbr_philo, tmp, 
//			philo->data->args->ttd - (time_ms * 1000));
			if (tmp < (philo->data->args->ttd - (time_ms * 1000)))
				philo_usleep(philo, tmp);
			else
				break;
*/

/*
(tt_eat + tt_sleep) / 2, perso
Si temps_avant_mort > (tt_eat + tt_sleep) /2  , je fait attendre cette durée
*/

bool	think_routine(t_philo *philo)
{
	t_timeval	time;
	long		time_ms;
	long		tmp;

	print_status(philo, THINKING_MSG);
	while (1)
	{
		gettimeofday(&time, NULL);
		time_ms = ((time.tv_sec - philo->last_lunch.tv_sec) * 1000) \
			+ ((time.tv_usec - philo->last_lunch.tv_usec) / 1000);
		tmp = (philo->data->args->tte + philo->data->args->tts) >> 1;
		if (tmp < (philo->data->args->ttd - (time_ms * 1000)))
		{
			if (philo_usleep(philo, tmp >> 1))
				return (true);
		}
		else
			break ;
	}
	return (false);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!check_death(philo->data))
	{
		if (eat_routine(philo))
			break ;
		if (check_death(philo->data))
			break ;
		if (sleep_routine(philo))
			break ;
		if (check_death(philo->data))
			break ;
		if (think_routine(philo))
			break ;
	}
	pthread_mutex_lock(&philo->mutex);
	if (!philo->is_alive)
		print_status(philo, DEAD_MSG);
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_lock(&philo->data->mutex);
	philo->data->has_stop++;
	pthread_mutex_unlock(&philo->data->mutex);
	return (NULL);
}
