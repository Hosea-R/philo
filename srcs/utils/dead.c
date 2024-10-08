#include "../Philosophers.h"

int	check_no_dead(t_config *config)
{
	int	no_dead_philos;

	pthread_mutex_lock(&config->config_mutex);
	no_dead_philos = config->no_dead_philos;
	pthread_mutex_unlock(&config->config_mutex);
	return (no_dead_philos);
}

void	verify_death(t_config *config, t_person *person)
{
	if (person->meal_count == config->eat_count && config->eat_count != -1)
	{
		pthread_mutex_lock(&config->config_mutex);
		config->no_dead_philos = 0;
		pthread_mutex_unlock(&config->config_mutex);
		return ;
	}
	if ((current_time() - person->last_meal_time) > (size_t)config->death_time)
	{
		pthread_mutex_lock(&config->config_mutex);
		config->no_dead_philos = 0;
		config->dead_philosopher = person->id;
		pthread_mutex_unlock(&config->config_mutex);
		person->current_state = 0;
	}
}

void	report_dead_philosopher(t_config *config)
{
	int	dead_philo_id;

	pthread_mutex_lock(&config->config_mutex);
	dead_philo_id = config->dead_philosopher;
	pthread_mutex_unlock(&config->config_mutex);
	if (dead_philo_id)
	{
		pthread_mutex_lock(&config->config_mutex);
		printf("\033[1;31m%ld %d died\033[0m\n", current_time() - config->start_time, dead_philo_id);
		pthread_mutex_unlock(&config->config_mutex);
	}
}
