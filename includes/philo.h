#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

# include "utils_philo.h"

typedef struct s_timep	t_timep;
typedef struct s_philo	t_philo;

/*
 *	nbp		:	nbr_philo
 *	ttd		:	time_to_die
 *	tte		:	time_to_eat
 *	tts		:	time_to_sleep
 *	ntpme	:	nbr_time_philosophers_must_eat
 */

struct s_timep
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
	pthread_mutex_t	lock;
};

#endif
