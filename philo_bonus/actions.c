#include "philo_bonus.h"

void	take_fork(t_person *person)
{
	sem_wait(person->philos->forks);
	sem_wait(person->philos->print);
	if (person->philos->sim_state != 0)
		printf("%7d %3d has taken a fork |\n", action_time(person), person->id);
	sem_post(person->philos->print);
}

void	eating(t_person *person)
{
	sem_wait(person->philos->death);
	person->time_of_death = get_time() + person->philos->time_to_die;
	sem_post(person->philos->death);
	sem_wait(person->philos->print);
	if (person->philos->sim_state != 0)
		printf("%7d %3d is eating \t🍝\n", action_time(person), person->id);
	sem_post(person->philos->print);
	if (person->philos->num_of_meals > 0 && person->philos->sim_state != 0)
	{
		ft_usleep(person->philos->time_to_eat);
		person->philos->num_of_meals--;
		if (person->philos->num_of_meals == 0 && person->philos->sim_state != 0)
		{
			sem_wait(person->philos->death);
			person->philos->sim_state -= 1;
			sem_post(person->philos->death);
		}
		return ;
	}
	if (person->philos->sim_state != 0)
		ft_usleep(person->philos->time_to_eat);
}

void	sleeping(t_person *person)
{
	sem_wait(person->philos->print);
	if (person->philos->sim_state != 0)
		printf("%7d %3d is sleeping\t💤\n", action_time(person), person->id);
	sem_post(person->philos->print);
	if (person->philos->sim_state != 0)
		ft_usleep(person->philos->time_to_sleep);
}

void	thinking(t_person *person)
{
	sem_wait(person->philos->print);
	if (person->philos->sim_state != 0)
		printf("%7d %3d is thinking\t💭\n", action_time(person), person->id);
	sem_post(person->philos->print);
}

void	dying(t_person *person)
{
	if (person->philos->sim_state == 0)
		return ;
	sem_wait(person->philos->death);
	person->philos->sim_state = 0;
	sem_wait(person->philos->print);
	printf("%7d %3d died \t💀\n", action_time(person), person->id);
	sem_post(person->philos->death);
}
