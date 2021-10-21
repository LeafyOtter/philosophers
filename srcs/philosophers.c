#include "philo.h"
#include "parsing_philo.h"

int	create_philosophers(int nbp, t_philo **philo_array)
{
	int i;

	i = -1;
	(*philo_array) = (t_philo *)malloc(sizeof(t_philo) * nbp);
	if (!(*philo_array))
		return (1);
	while (++i < nbp)
		(*philo_array)[i] = (t_philo){i + 1, 0, true, {0}};
	return (0);
}


int	main(int ac, char **av)
{
	t_timep	timep;
	t_philo *philo_array;
	struct timeval	tv1;
	struct timeval	tv2;

	timep = (t_timep){0, 0, 0, 0, 0};
	gettimeofday(&tv1, NULL);
	if (parsing(ac, av, &timep))
		return (1);
	if (create_philosophers(timep.nbp, &philo_array))
		return (1);
//	for (int i = 0; i < timep.nbp; i++)
//		printf("nbr_philo : %zu nbr_lunch : %zu is_alive : %s\n", \
//				philo_array[i].nbr_philo, philo_array[i].nbr_lunch, \
//				philo_array[i].is_alive ? "true" : "false");
	free(philo_array);
}
