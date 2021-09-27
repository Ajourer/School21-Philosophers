#include "philosophers.h"

void	*even_philos(void *p)
{
	t_person	*person;

	person = (t_person *)p;
	while (person->philos->sim_state != 0 && person->philos->num_of_meals != 0)
	{
		pthread_mutex_lock(person->right_fork);
		take_fork(person);
		pthread_mutex_lock(person->left_fork);
		take_fork(person);
		eating(person);
		pthread_mutex_unlock(person->right_fork);
		pthread_mutex_unlock(person->left_fork);
		sleeping(person);
		thinking(person);
		usleep(100);
	}
	return (0);
}

void	*odd_philos(void *p)
{
	t_person	*person;

	person = (t_person *)p;
	while (person->philos->sim_state != 0 && person->philos->num_of_meals != 0)
	{
		pthread_mutex_lock(person->left_fork);
		take_fork(person);
		pthread_mutex_lock(person->right_fork);
		take_fork(person);
		eating(person);
		pthread_mutex_unlock(person->left_fork);
		pthread_mutex_unlock(person->right_fork);
		sleeping(person);
		thinking(person);
		usleep(100);
	}
	return (0);
}

static int	dead_or_alive(t_person *person)
{
	int	result;

	pthread_mutex_lock(person->philos->death);
	result = person->time_of_death < get_time();
	pthread_mutex_unlock(person->philos->death);
	return (result);
}

static void	simulation_check(t_person *person, unsigned long phil_num)
{
	unsigned long	i;

	usleep(100);
	while (1)
	{
		i = 0;
		while (i < phil_num)
		{
			if (person[i].philos->sim_state == 0)
				return ;
			if (dead_or_alive(&person[i]) == DEAD
				&& person[i].philos->sim_state != 0 && person[i].meals_num != 0)
			{
				dying(&person[i]);
				return ;
			}
			i++;
		}
	}
}

int	run_threads(t_philos *philos, t_person *person)
{
	int	i;

	i = -1;
	while (++i < philos->phil_num)
	{
		if (i % 2 == 0)
		{
			if (pthread_create(&(philos->th[i]), NULL,
					&even_philos, &(person[i])) != 0)
				return (printf("Error: pthread_create\n"));
		}
		else
		{
			if (pthread_create(&(philos->th[i]), NULL,
					&odd_philos, &(person[i])) != 0)
				return (printf("Error: pthread_create\n"));
		}
	}
	i = -1;
	while (++i < philos->phil_num)
		if (pthread_detach(philos->th[i]) != 0)
			return (-1);
	simulation_check(person, philos->phil_num);
	ft_usleep(philos->time_to_die * 2);
	return (0);
}
