#ifndef SIMULATION_H
# define SIMULATION_H

# define FORK_MSG "has taken a fork"
# define EATING_MSG "is eating"
# define SLEEPING_MSG "is sleeping"
# define THINKING_MSG "is thinking"
# define DEAD_MSG "died"

int	start_simulation(t_data *data, t_philo **philo_array);

#endif