#ifndef SIMULATION_H
# define SIMULATION_H

# define FORK_MSG "has taken a fork"
# define EATING_MSG "is eating"
# define SLEEPING_MSG "is sleeping"
# define THINKING_MSG "is thinking"
# define DEAD_MSG "died"

# define WAIT_TIME 7500

int		start_simulation(t_data *data, t_philo **philo_array);
void	print_status(t_philo *philo, char *str);
bool	check_death(t_data *data);
bool	philo_usleep(t_philo *philo, suseconds_t time_to_wait);

void	*routine(void *arg);

#endif