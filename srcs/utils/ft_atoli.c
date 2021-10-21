int	ft_atoli(long int *nbr, char *nptr)
{
	int	sign;
	int	ret;

	*nbr = 0;
	ret = 1;
	sign = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		(nptr)++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		ret = 0;
		*nbr *= 10;
		*nbr += (*nptr - '0') * sign;
		nptr++;
	}
	return (ret);
}
