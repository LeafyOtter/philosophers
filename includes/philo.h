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
	size_t		nbp;
	suseconds_t	ttd;
	suseconds_t	tte;
	suseconds_t	tts;
	long		ntpme;
};

struct s_philo
{
	size_t			nbr_philo;
	long			nbr_lunch;
	t_timeval		last_lunch;
	bool			is_alive;
	bool			lunch;
	pthread_mutex_t	mutex;
	t_data			*data;
	pthread_mutex_t	left;
	pthread_mutex_t	*right;
};

struct s_data
{
	t_args			*args;
	t_timeval		start_sim;
	size_t			nbr_philo_fed;
	bool			should_stop;
	size_t			has_stop;
	pthread_mutex_t	mutex;
	pthread_t		*tid;
};

/*
 *	[ PARSING ]
 */

int	parsing(int argc, char **argv, t_args *args);

/*
 *	[ UTILS ]
 */

int	ft_atoli(long int *nbr, char *nptr);

#endif
