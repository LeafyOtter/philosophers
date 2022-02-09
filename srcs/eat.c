#include "philo.h"
#include "simulation.h"
#include "error_message.h"

static void	multi_mutex_unlock(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left);
	pthread_mutex_unlock(philo->right);
}

static bool	eat_helper(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->nbr_lunch++;
	gettimeofday(&philo->last_lunch, NULL);
	pthread_mutex_unlock(&philo->mutex);
	print_status(philo, EATING_MSG);
	if (philo_usleep(philo, philo->data->args->tte))
		return (multi_mutex_unlock(philo), true);
	return (multi_mutex_unlock(philo), false);
}

static bool	left_first(t_philo *philo)
{
	pthread_mutex_lock(&philo->left);
	if (check_death(philo->data))
		return (pthread_mutex_unlock(&philo->left), true);
	print_status(philo, FORK_MSG);
	if (philo->data->args->nbp == 1)
	{
		philo_usleep(philo, philo->data->args->ttd);
		return (pthread_mutex_unlock(&philo->left), true);
	}
	pthread_mutex_lock(philo->right);
	if (check_death(philo->data))
		return (multi_mutex_unlock(philo), true);
	print_status(philo, FORK_MSG);
	return (false);
}

static bool	right_first(t_philo *philo)
{
	static int	i = 0;

	if (!i)
	{
		usleep(50);
		i++;
	}
	pthread_mutex_lock(philo->right);
	if (check_death(philo->data))
		return (pthread_mutex_unlock(philo->right), true);
	print_status(philo, FORK_MSG);
	pthread_mutex_lock(&philo->left);
	if (check_death(philo->data))
		return (multi_mutex_unlock(philo), true);
	print_status(philo, FORK_MSG);
	return (false);
}

bool	eat_routine(t_philo *philo)
{
	if (philo->nbr_philo % 2)
	{
		if (left_first(philo))
			return (true);
	}
	else
	{
		if (right_first(philo))
			return (true);
	}
	return (eat_helper(philo));
}
