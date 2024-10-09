/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:43:13 by mrazanad          #+#    #+#             */
/*   Updated: 2024/10/09 08:06:57 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philosophers.h"

void	setup_priority(t_config *config)
{
	int	i;
	int	start_priority;

	i = 0;
	start_priority = 1;
	config->priority_order = malloc(sizeof(int) * (config->num_philo
				/ 2));
	if (!config->priority_order)
	{
		printf("Error\n");
		return ;
	}
	while (i < config->num_philo / 2)
	{
		config->priority_order[i] = start_priority;
		start_priority += 2;
		i++;
	}
}

void	calculate_priority(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->num_philo / 2)
	{
		config->priority_order[i] = config->priority_order[i] + 1;
		if (config->priority_order[i] > config->num_philo)
			config->priority_order[i] = 1;
		i++;
	}
}

int	check_priority(t_config *config, t_person *person)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&config->config_mutex);
	while (i < config->num_philo / 2)
	{
		if (config->priority_order[i] == person->id)
		{
			pthread_mutex_unlock(&config->config_mutex);
			return (1);
		}
		i++;
	}
	pthread_mutex_unlock(&config->config_mutex);
	return (0);
}

void	update_priority_order(t_config *config)
{
	while (check_no_dead(config))
	{
		pthread_mutex_lock(&config->config_mutex);
		if (config->finished_count >= config->num_philo / 2)
		{
			config->finished_count = 0;
			calculate_priority(config);
		}
		pthread_mutex_unlock(&config->config_mutex);
		delay(0);
	}
}
