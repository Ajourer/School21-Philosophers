#include "philo_bonus.h"

static void	init_philos(int argc, char **argv, t_philos *philos)
{
	philos->phil_num = ft_atoi(argv[1]);
	philos->time_to_die = ft_atoi(argv[2]);
	philos->time_to_eat = ft_atoi(argv[3]);
	philos->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philos->num_of_meals = ft_atoi(argv[5]);
	else
		philos->num_of_meals = -1;
	philos->forks = sem_open("forks", O_CREAT, 644, philos->phil_num);
	philos->print = sem_open("print", O_CREAT, 644, 1);
	philos->death = sem_open("death", O_CREAT, 644, 1);
	philos->took_both = sem_open("took_both", O_CREAT, 644, 1);
	philos->sim_state = 1;
	philos->count = 0;
	philos->start_t = get_time();
}

void	unlink_all(void)
{
	sem_unlink("death");
	sem_unlink("forks");
	sem_unlink("took_both");
	sem_unlink("print");
}

int	main(int argc, char **argv)
{
	t_philos	philos;
	pid_t		*philo_pid;

	unlink_all();
	if (parse_params(argc, argv) != 0)
		return (-1);
	init_philos(argc, argv, &philos);
	philo_pid = malloc(sizeof(pid_t) * philos.phil_num);
	if (!philo_pid)
		return (-1);
	create_processes(philo_pid, &philos);
	end_processes(philo_pid, &philos);
	free(philo_pid);
	return (0);
}
