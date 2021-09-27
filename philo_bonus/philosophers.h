#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# define DEAD 1

typedef struct s_philos
{
	int				phil_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;
	int				sim_state;
	unsigned long	start_t;
	pthread_t		*th;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	pthread_mutex_t	*death;
}				t_philos;

typedef struct s_person
{
	t_philos		*philos;
	int				id;
	int				meals_num;
	unsigned long	time_of_death;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}				t_person;

int				ft_atoi(const char *str);
int				parse_params(int argc, char **argv);
unsigned long	get_time(void);
int				action_time(t_person *person);
void			ft_usleep(unsigned long interval);
int				run_threads(t_philos *philos, t_person *person);
void			take_fork(t_person *person);
void			eating(t_person *person);
void			sleeping(t_person *person);
void			thinking(t_person *person);
void			dying(t_person *person);

#endif
