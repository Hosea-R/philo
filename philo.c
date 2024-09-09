/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:26:07 by mrazanad          #+#    #+#             */
/*   Updated: 2024/09/09 13:26:08 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_life(void *arg)
{
	t_philosopher	*philosopher;
	t_table			*table;

	philosopher = (t_philosopher *)arg;
	table = philosopher->table;
	while (!table->stop)
	{
		take_forks(philosopher);
		eating(philosopher);
		release_forks(philosopher);
		sleeping(philosopher);
		thinking(philosopher);
	}
	return (NULL);
}
