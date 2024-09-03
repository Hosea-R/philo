#include "philo.h"

void	take_forks(t_philosopher *philosopher)
{
	t_table	*table;
	int		left_fork;
	int		right_fork;

	table = philosopher->table;
	left_fork = philosopher->id;
	right_fork = (philosopher->id + 1) % table->num_philosophers;
	pthread_mutex_lock(&table->forks[left_fork].mutex);
	pthread_mutex_lock(&table->forks[right_fork].mutex);
	print_action(table, philosopher->id, "has taken a fork");
	print_action(table, philosopher->id, "has taken a fork");
}

void	release_forks(t_philosopher *philosopher)
{
	t_table	*table;
	int		left_fork;
	int		right_fork;

	table = philosopher->table;
	left_fork = philosopher->id;
	right_fork = (philosopher->id + 1) % table->num_philosophers;
	pthread_mutex_unlock(&table->forks[left_fork].mutex);
	pthread_mutex_unlock(&table->forks[right_fork].mutex);
}

void	eating(t_philosopher *philosopher)
{
	t_table	*table;

	table = philosopher->table;
	print_action(table, philosopher->id, "is eating");
	philosopher->last_meal = current_time();
	philosopher->times_eaten++;
	usleep(table->time_to_eat * 1000);
}

#include "philo.h"

void	thinking(t_philosopher *philosopher)
{
	t_table	*table;

	table = philosopher->table;
	print_action(table, philosopher->id, "is thinking");
}

void	sleeping(t_philosopher *philosopher)
{
	t_table	*table;

	table = philosopher->table;
	print_action(table, philosopher->id, "is sleeping");
	usleep(table->time_to_sleep * 1000);
}
