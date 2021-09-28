#include "philo_bonus.h"

static void	*circle_of_life(void *p)
{
	t_person	*person;

	person = (t_person *)p;
	while (person->philos->sim_state != 0)
	{
		sem_wait(person->philos->took_both);
		take_fork(person);
		take_fork(person);
		sem_post(person->philos->took_both);
		eating(person);
		sem_post(person->philos->forks);
		sem_post(person->philos->forks);
		if (person->philos->num_of_meals == 0)
		{
			sem_wait(person->philos->death);
			person->philos->sim_state = 0;
			sem_post(person->philos->death);
			return (0);
		}
		sleeping(person);
		thinking(person);
		usleep (50);
	}
	return (0);
}

static int	dead_or_alive(t_person *person)
{
	int	result;

	sem_wait(person->philos->death);
	result = person->time_of_death < get_time();
	sem_post(person->philos->death);
	return (result);
}

static void	each_process(t_philos *philos)
{
	t_person	person;

	person.philos = philos;
	person.time_of_death = get_time() + philos->time_to_die;
	person.id = philos->count + 1;
	pthread_create(&person.th, NULL, &circle_of_life, &person);
	while (person.philos->sim_state != 0)
	{
		if (dead_or_alive(&person) == DEAD)
		{
			dying(&person);
			exit(0);
		}
	}
	pthread_join(person.th, NULL);
	exit(FULL);
}

void	create_processes(pid_t *philo_pid, t_philos *philos)
{
	int	pid;

	philos->start_t = get_time();
	while (philos->count < philos->phil_num)
	{
		pid = fork();
		if (pid == 0)
		{
			free(philo_pid);
			each_process(philos);
		}
		else
			philo_pid[philos->count] = pid;
		philos->count++;
	}
}

void	end_processes(pid_t *philo_pid, t_philos *philos)
{
	int	i;
	int	status;

	i = 0;
	while (i < philos->phil_num)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) != FULL)
		{
			i = -1;
			while (++i < philos->phil_num)
				kill(philo_pid[i], SIGQUIT);
			return ;
		}
		i++;
	}
}
