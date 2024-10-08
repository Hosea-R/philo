#include "../Philosophers.h"

void	initialize_config(t_config *config, int argc, char *argv[])
{
	config->num_philosophers = string_to_int(argv[1]);
	config->death_time = string_to_int(argv[2]);
	config->eat_duration = string_to_int(argv[3]);
	config->sleep_duration = string_to_int(argv[4]);
	config->eat_count = -1;

	if (argc == 6)
		config->eat_count = string_to_int(argv[5]);

	config->finished_count = 0;
	config->no_dead_philos = 1;
	config->dead_philosopher = 0;

	if (pthread_mutex_init(&config->config_mutex, NULL))
	{
		printf("Error initializing mutex\n");
		return;
	}
	initialize_people(config);
	setup_priority(config);
}

void	cleanup_config(t_config *config)
{
	int i;
	void *result;

	i = 0;
	while (i < config->num_philosophers)
	{
		pthread_join(config->people[i]->thread_id, &result);
		free(result);
		i++;
	}
	while (i--)
	{
		pthread_mutex_destroy(&config->people[i]->person_mutex);
		pthread_mutex_destroy(config->people[i]->right_fork);
		free(config->people[i]->right_fork);
		free(config->people[i]);
	}
	pthread_mutex_destroy(&config->config_mutex);
	free(config->priority_order);
	free(config->people);
}
