#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_fork
{
	pthread_mutex_t mutex;
	int             in_use;
} t_fork;

typedef struct s_philosopher
{
	int             id;
	int             times_eaten;
	long            last_meal;
	pthread_t       thread;
	struct s_table  *table;
} t_philosopher;

typedef struct s_table
{
	int             num_philosophers;
	int             time_to_die;
	int             time_to_eat;
	int             time_to_sleep;
	int             max_meals;
	int             stop;
	long            start_time;
	t_fork          *forks;
	t_philosopher   *philosophers;
	pthread_mutex_t print_lock;
} t_table;

void    init_data(t_table *table, int argc, char **argv);
void    destroy_data(t_table *table);
void    *philosopher_life(void *arg);
void    take_forks(t_philosopher *philosopher);
void    release_forks(t_philosopher *philosopher);
void    eating(t_philosopher *philosopher);
void    sleeping(t_philosopher *philosopher);
void    thinking(t_philosopher *philosopher);
void    print_action(t_table *table, int philosopher_id, const char *action);
void    check_death(t_table *table);
long    current_time(void);

#endif
