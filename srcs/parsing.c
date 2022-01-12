#include "philo.h"
#include "error_message.h"

static int	check_nbr_args(
		int argc,
		char *name)
{
	if (argc <= 4)
		printf("%s: %s%s\n", name, MISSING_ARGS, EXPECTED_ARGS);
	if (argc > 6)
		printf("%s: %s%s\n", name, TM_ARGS, EXPECTED_ARGS);
	if (argc <= 4 || argc > 6)
		return (1);
	return (0);
}

static int	convert_args(
		int argc,
		char **argv,
		long *array)
{
	int			i;
	long int	nbr;

	i = 1;
	while (i < argc)
	{
		if (ft_atoli(&nbr, argv[i]))
		{
			printf("%s: %s%s%i%s\n", argv[0], INVALID_ARG, ARG_NBR, i, ARG_STR);
			return (1);
		}
		array[i - 1] = nbr;
		i++;
	}
	return (0);
}

static int	verify_args(
		int argc,
		char *name,
		long *array,
		t_args *args)
{
	int		i;
	long	*current;

	i = 0;
	current = &args->nbp;
	while (i < (argc - 1))
	{
		if (array[i] < 0)
		{
			printf("%s: %s%s%i%s\n", name, INVALID_ARG, ARG_NBR, i, ARG_NEG);
			return (1);
		}
		*current = array[i];
		current++;
		i++;
	}
	return (0);
}

/*
 *	parsing :
 *		- check right nb of args
 *		- convert args to long
 *		- verify arguments and stock them;
 */

int	parsing(
		int argc,
		char **argv,
		t_args *args)
{
	long	array[5];

	if (check_nbr_args(argc, argv[0]))
		return (1);
	if (convert_args(argc, argv, array))
		return (1);
	if (verify_args(argc, argv[0], array, args))
		return (1);
	return (0);
}
