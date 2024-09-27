#include "Philosophers.h"

t_person	*create_person(int id)
{
	t_person	*person;

	person = malloc(sizeof(t_person));
	if (!person)
		return (NULL);
	person->thread_id = 0;
	person->id = id;
	person->current_state = -1;
	person->meal_count = 0;
	person->last_meal_time = 0;
	person->right_fork = malloc(sizeof(pthread_mutex_t));
	if (!person->right_fork)
		return (NULL);
	if (pthread_mutex_init(person->right_fork, NULL))
		return (NULL);
	person->left_fork = NULL;
	return (person);
}

void	initialize_people(t_config *config)
{
	int	i;

	i = 0;
	config->people = malloc(sizeof(t_person *) * config->num_philosophers);
	if (!config->people)
		return ;
	while (i < config->num_philosophers)
	{
		config->people[i] = create_person(i + 1);
		pthread_mutex_init(&config->people[i]->person_mutex, NULL);
		i++;
	}
	while (i--)
	{
		if (i == 0)
			config->people[i]->left_fork = config->people[config->num_philosophers - 1]->right_fork;
		else
			config->people[i]->left_fork = config->people[i - 1]->right_fork;
	}
}

void	start_simulation(t_config *config)
{
	int		i;
	t_args	*arg;

	i = 0;
	config->start_time = current_time();
	while (i < config->num_philosophers)
	{
		arg = malloc(sizeof(t_args));
		arg->config = config;
		arg->person = config->people[i];
		arg->person->last_meal_time = current_time();
		pthread_create(&arg->person->thread_id, NULL, philosopher_routine, (void *)arg);
		i++;
	}
}
