#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <semaphore.h>
# include <signal.h>
# define DEAD 1
# define FULL 1

typedef struct s_philos
{
	int				phil_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;
	int				sim_state;
	int				count;
	unsigned long	start_t;
	sem_t			*forks;
	sem_t			*took_both;
	sem_t			*print;
	sem_t			*death;
}				t_philos;

typedef struct s_person
{
	t_philos		*philos;
	int				id;
	unsigned long	time_of_death;
	pthread_t		th;
}				t_person;

int				ft_atoi(const char *str);
int				parse_params(int argc, char **argv);
unsigned long	get_time(void);
int				action_time(t_person *person);
void			ft_usleep(unsigned long interval);
void			take_fork(t_person *person);
void			eating(t_person *person);
void			sleeping(t_person *person);
void			thinking(t_person *person);
void			dying(t_person *person);
void			create_processes(pid_t *philo_pid, t_philos *philos);
void			end_processes(pid_t *philo_pid, t_philos *philos);

#endif
