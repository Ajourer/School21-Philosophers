#include "philosophers.h"

void	take_fork(t_person *person)
{
	pthread_mutex_lock(person->philos->print);
	if (person->philos->sim_state != 0)
		printf("%d %d has taken a fork\n", action_time(person), person->id);
	pthread_mutex_unlock(person->philos->print);
}

void	eating(t_person *person)
{
	pthread_mutex_lock(person->philos->death);
	person->time_of_death = get_time() + person->philos->time_to_die;
	pthread_mutex_unlock(person->philos->death);
	pthread_mutex_lock(person->philos->print);
	if (person->philos->sim_state != 0)
		printf("%d %d is eating 🍴\n", action_time(person), person->id);
	pthread_mutex_unlock(person->philos->print);
	if (person->meals_num > 0 && person->philos->sim_state != 0)
	{
		ft_usleep(person->philos->time_to_eat);
		person->meals_num--;
		if (person->meals_num == 0 && person->philos->sim_state != 0)
		{
			pthread_mutex_lock(person->philos->death);
			person->philos->sim_state -= 1;
			pthread_mutex_unlock(person->philos->death);
		}
		return ;
	}
	if (person->philos->sim_state != 0)
		ft_usleep(person->philos->time_to_eat);
}

void	sleeping(t_person *person)
{
	pthread_mutex_lock(person->philos->print);
	if (person->philos->sim_state != 0)
		printf("%d %d is sleeping 💤\n", action_time(person), person->id);
	pthread_mutex_unlock(person->philos->print);
	if (person->philos->sim_state != 0)
		ft_usleep(person->philos->time_to_sleep);
}

void	thinking(t_person *person)
{
	pthread_mutex_lock(person->philos->print);
	if (person->philos->sim_state != 0)
		printf("%d %d is thinking 💭\n", action_time(person), person->id);
	pthread_mutex_unlock(person->philos->print);
}
