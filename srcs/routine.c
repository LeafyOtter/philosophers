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
	print_status(philo, EATING_MSG);
	pthread_mutex_lock(&philo->mutex);
	philo->nbr_lunch++;
	gettimeofday(&philo->last_lunch, NULL);
	pthread_mutex_unlock(&philo->mutex);
	if (philo_usleep(philo, philo->data->args->tte))
		return (multi_mutex_unlock(philo), true);
	return (multi_mutex_unlock(philo), false);
}

//	if (philo->nbr_philo != (size_t)philo->data->args->nbp)

bool	eat_routine(t_philo *philo)
{
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
		print_status(philo, THINKING_MSG);
		usleep(500);
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
