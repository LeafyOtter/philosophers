#include "philo.h"
#include "simulation.h"
#include "error_message.h"

void	multi_mutex_unlock(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left);
	pthread_mutex_unlock(philo->right);
}

bool	eat_helper(t_philo *philo)
{
//	print_status(philo, EATING_MSG);
	pthread_mutex_lock(&philo->mutex);
	philo->nbr_lunch++;
	gettimeofday(&philo->last_lunch, NULL);
	pthread_mutex_unlock(&philo->mutex);
	print_status(philo, EATING_MSG);
	if (philo_usleep(philo, philo->data->args->tte))
		return (multi_mutex_unlock(philo), true);
//	print_status(philo, "IS DEBUGGING");
	return (multi_mutex_unlock(philo), false);
}

//	if (philo->nbr_philo != (size_t)philo->data->args->nbp)

bool	eat_routine(t_philo *philo)
{
	static int i = 0;
	if (philo->nbr_philo % 2)
	{
		pthread_mutex_lock(&philo->left);
		if (check_death(philo->data))
			return (pthread_mutex_unlock(&philo->left), true);
		print_status(philo, FORK_MSG);
		if (philo->data->args->nbp == 1)
		{
			if (philo_usleep(philo, philo->data->args->ttd))
				return (pthread_mutex_unlock(&philo->left), true);
		}
		pthread_mutex_lock(philo->right);
		if (check_death(philo->data))
			return (multi_mutex_unlock(philo), true);
		print_status(philo, FORK_MSG);
	}
	else
	{
		if (!i)
		{	usleep(75);i++;}
		pthread_mutex_lock(philo->right);
		if (check_death(philo->data))
			return (pthread_mutex_unlock(philo->right), true);
		print_status(philo, FORK_MSG);
//		printf("hi?\n");
		pthread_mutex_lock(&philo->left);
		if (check_death(philo->data))
			return (multi_mutex_unlock(philo), true);
//		printf("hi? %zu\n", philo->nbr_philo);
		print_status(philo, FORK_MSG);
	}
	return (eat_helper(philo));
}

bool	sleep_routine(t_philo *philo)
{
	print_status(philo, SLEEPING_MSG);
	if (philo_usleep(philo, philo->data->args->tts))
		return (true);
	return (false);
}

void	*routine(void *arg)
{
	t_timeval	time;
	long	time_ms;
	long	tmp;
	t_philo	*philo;
//	extern int fd;

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
		print_status(philo, THINKING_MSG);
		while (1)
		{
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
		}
	}
	pthread_mutex_lock(&philo->mutex);
//	printf("Quitting %zu\n", philo->nbr_philo);
	if (!philo->is_alive)
		print_status(philo, DEAD_MSG);
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_lock(&philo->data->mutex);
	philo->data->has_stop++;
	pthread_mutex_unlock(&philo->data->mutex);
	return (NULL);
}


/*
(tt_eat + tt_sleep) / 2, perso
Si temps_avant_mort > (tt_eat + tt_sleep) /2  , je fait attendre cette durée
*/