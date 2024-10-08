/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:42:56 by mrazanad          #+#    #+#             */
/*   Updated: 2024/10/08 12:42:57 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philosophers.h"

void	perform_eating(t_config *config, t_person *person)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	first_fork = person->right_fork;
	second_fork = person->left_fork;
	if (person->id % 2)
	{
		first_fork = person->left_fork;
		second_fork = person->right_fork;
	}
	person->last_meal_time = current_time();
	pthread_mutex_lock(first_fork);
	display_status(config, person, -1);
	pthread_mutex_lock(second_fork);
	display_status(config, person, -1);
	display_status(config, person, 2);
	person->current_state = 2;
	delay(config->eat_duration);
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_lock(&config->config_mutex);
	config->finished_count++;
	pthread_mutex_unlock(&config->config_mutex);
	person->meal_count++;
	verify_death(config, person);
}

void	perform_sleeping(t_config *config, t_person *person)
{
	if (check_no_dead(config))
	{
		display_status(config, person, 3);
		person->current_state = 3;
		delay(config->sleep_duration);
		person->current_state = -1;
		if (config->sleep_duration <= 1)
		{
			while (check_priority(config, person) && check_no_dead(config))
				delay(0);
		}
		verify_death(config, person);
	}
}

void	perform_thinking(t_config *config, t_person *person)
{
	if (check_no_dead(config))
	{
		display_status(config, person, 1);
		person->current_state = 1;
		verify_death(config, person);
	}
}
