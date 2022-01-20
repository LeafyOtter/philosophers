# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <unistd.h>

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;
typedef struct timeval	t_timeval;

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
//	t_args			*args;
	t_timeval		start_sim;
	long			nbr_philo_fed;
	bool			should_stop;
	long			has_stop;
	pthread_mutex_t	mutex;
	pthread_t		*tid;
};

void	think_routine(t_philo *philo)
{
	t_timeval	time;
	t_timeval	time_stamp;
	long		time_ms;

	usleep(21);
	gettimeofday(&time, NULL);
	time_stamp.tv_sec = time.tv_sec - philo->data->start_sim.tv_sec;
	time_stamp.tv_usec = time.tv_usec - philo->data->start_sim.tv_usec;
	time_ms = time_stamp.tv_sec  * 1000 + time_stamp.tv_usec / 1000;
	printf("DEBUG : %li\n", philo->data->start_sim.tv_sec  * 1000 + philo->data->start_sim.tv_usec / 1000);
	printf("%li %zu is thinking\n", time_ms, philo->nbr_philo);
}

int main(void)
{
	t_philo	philo;
	t_data	data;

	gettimeofday(&data.start_sim, NULL);
	philo = (t_philo){1, 0, true, &data, 0};
	think_routine(&philo);
	usleep(15000);
	think_routine(&philo);
}
/*
struct timeval  tv;
gettimeofday(&tv, NULL);

double time_in_mill = 
         (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ; // convert tv_sec & tv_usec to millisecond

Tags:
Misc Example
*/