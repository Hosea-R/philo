#include "philo.h"

void	init_data(t_table *table, int argc, char **argv)
{
	int	i;

	table->num_philosophers = atoi(argv[1]);
	table->time_to_die = atoi(argv[2]);
	table->time_to_eat = atoi(argv[3]);
	table->time_to_sleep = atoi(argv[4]);
	table->max_meals = (argc == 6) ? atoi(argv[5]) : -1;
	table->stop = 0;
	table->forks = malloc(sizeof(t_fork) * table->num_philosophers);
	table->philosophers = malloc(sizeof(t_philosopher)
			* table->num_philosophers);
	i = 0;
	while (i < table->num_philosophers)
	{
		pthread_mutex_init(&table->forks[i].mutex, NULL);
		table->forks[i].in_use = 0;
		i++;
	}
	i = 0;
	while (i < table->num_philosophers)
	{
		table->philosophers[i].id = i;
		table->philosophers[i].times_eaten = 0;
		table->philosophers[i].last_meal = current_time();
		table->philosophers[i].table = table;
		i++;
	}
	pthread_mutex_init(&table->print_lock, NULL);
}

void	destroy_data(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philosophers)
	{
		pthread_mutex_destroy(&table->forks[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&table->print_lock);
	free(table->forks);
	free(table->philosophers);
}
