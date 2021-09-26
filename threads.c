#include "philosophers.h"

void	*even_philos(void *p)
{
	t_person *person;

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
	t_person *person;

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

int run_threads(t_philos *philos, t_person *person)
{
	int	i;

	i = -1;
	while (++i < philos->phil_num)
	{
		if (i % 2 == 0)
		{
			if (pthread_create(&(philos->th[i]), NULL, &even_philos, &(person[i])) != 0)
				return (-1);
		}
		else
		{
			if (pthread_create(&(philos->th[i]), NULL, &odd_philos, &(person[i])) != 0)
				return (-1);
		}
	}
	i = -1;
	while (++i < philos->phil_num)
		if (pthread_detach(philos->th[i]) != 0)
			return (-1);

	return (0);
}
