#include "philosophers.h"

static int	init_mutex(t_philos *philos)
{
	int	i;

	philos->forks = malloc(sizeof(pthread_mutex_t) * philos->phil_num);
	philos->print = malloc(sizeof(pthread_mutex_t));
	philos->death = malloc(sizeof(pthread_mutex_t));
	if (!(philos->forks))
		return (printf("Error: malloc\n"));
	i = -1;
	while (++i < philos->phil_num)
	{
		if (pthread_mutex_init(&philos->forks[i], NULL) != 0)
			return (printf("Error: mutex init"));
	}
	if (pthread_mutex_init(philos->print, NULL) != 0 ||
			pthread_mutex_init(philos->death, NULL) != 0)
		return (printf("Error: mutex init"));
	return (0);
}

static int init_philos(int argc, char **argv, t_philos *philos)
{
	philos->phil_num = ft_atoi(argv[1]);
	philos->time_to_die = ft_atoi(argv[2]);
	philos->time_to_eat = ft_atoi(argv[3]);
	philos->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philos->num_of_meals = ft_atoi(argv[5]);
	else
		philos->num_of_meals = -1;
	philos->th = malloc(sizeof(pthread_t) * philos->phil_num);
	if (!(philos->th))
		return (printf("Error: malloc\n"));
	if (init_mutex(philos) != 0)
		return (-1);
	philos->sim_state = philos->phil_num;
	philos->start_t = get_time();
	return (0);
}

static void init_persons(t_philos *philos, t_person *person)
{
	int	i;
	int	n;

	n = philos->phil_num;
	i = -1;
	while (++i < philos->phil_num)
	{
		person[i].philos = philos;
		person[i].id = i + 1;
		person[i].meals_num = philos->num_of_meals;
		person[i].time_of_death = get_time() + philos->time_to_die;
		person[i].left_fork = philos->forks[i];
		person[i].right_fork = philos->forks[(i + 1) % n];
	}
}

static void	free_all(t_philos *philos, t_person *person)
{
	int	i;

	i = -1;
	while (++i < philos->phil_num)
		pthread_mutex_destroy(&philos->forks[i]);
	pthread_mutex_destroy(philos->print);
	pthread_mutex_destroy(philos->death);
	free(philos->forks);
	free(philos->print);
	free(philos->death);
	free(person);
}

int	main(int argc, char **argv)
{
	int			i;
	t_philos	philos;
	t_person	*person;

	if (parse_params(argc, argv) != 0)
		return (-1);
	if (init_philos(argc, argv, &philos) != 0)
		return (-1);
	person = malloc(sizeof(t_person) * philos.phil_num);
	init_persons(&philos, person);
	if (run_threads(&philos, person) != 0)
		return (-1);
	free_all(&philos, person);
	return (0);
}
