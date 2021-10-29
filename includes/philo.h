#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

# define PTHREAD_MUTEX_INIT PTHREAD_MUTEX_INITIALIZER

typedef struct s_args	t_args;
typedef struct s_philo	t_philo;
typedef struct s_data	t_data;
typedef struct timeval	t_timeval;

/*
 *	nbp		:	nbr_philo
 *	ttd		:	time_to_die
 *	tte		:	time_to_eat
 *	tts		:	time_to_sleep
 *	ntpme	:	nbr_time_philosophers_must_eat
 */

struct s_args
{
	long		nbp;
	suseconds_t	ttd;
	suseconds_t	tte;
	suseconds_t	tts;
	long		ntpme;
};

struct s_philo
{
	size_t			nbr_philo;
	size_t			nbr_lunch;
	bool			is_alive;
	t_data			*data;
	pthread_mutex_t	lock;
};

struct s_data
{
	t_args		*args;
	t_timeval	start_sim;
	bool		should_stop;
	long		nbr_philo_fed;
	pthread_t	*tid;
};

#endif
