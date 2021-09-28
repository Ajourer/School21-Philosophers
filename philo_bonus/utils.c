#include "philo_bonus.h"

int	ft_atoi(const char *str)
{
	int	minus;
	int	i;
	int	nb;

	minus = 1;
	i = 0;
	nb = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		++i;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus *= (-1);
		++i;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		nb = nb * 10 + (str[i] - '0');
		++i;
	}
	nb *= minus;
	return (nb);
}

int	parse_params(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (printf("Error: invalid number of arguments\n"));
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (printf("Error: invalid argument\n"));
			j++;
		}
		i++;
	}
	if (ft_atoi(argv[1]) < 0 || ft_atoi(argv[1]) > 200)
		return (printf("Error: invalid number of philosophers\n"));
	return (0);
}

unsigned long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	action_time(t_person *person)
{
	return (get_time() - person->philos->start_t);
}

void	ft_usleep(unsigned long interval)
{
	unsigned long	start;

	start = get_time();
	while (get_time() - start < interval)
		usleep(500);
}
