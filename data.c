/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:25:58 by mrazanad          #+#    #+#             */
/*   Updated: 2024/09/09 13:39:05 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(const char *nptr)
{
	int	i;
	int	signe;
	int	resultat;

	i = 0;
	signe = 1;
	resultat = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	while (nptr[i] == '+' || nptr[i] == '-')
	{
		if (!(nptr[i + 1] >= '0' && nptr[i + 1] <= '9'))
			return (0);
		if (nptr[i] == '-')
			signe *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		resultat = resultat * 10 + nptr[i] - '0';
		i++;
	}
	return (resultat * signe);
}

int	init_data(t_table *table, int argc, char **argv)
{
	int	i;

	table->num_philosophers = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	//table->max_meals = (argc == 6) ? ft_atoi(argv[5]) : -1;
	if (argc == 6)
		table->max_meals = ft_atoi(argv[5]);
	else
		table->max_meals = -1;
	table->stop = 0;
	table->forks = malloc(sizeof(t_fork) * table->num_philosophers);
	table->philosophers = malloc(sizeof(t_philosopher)
			* table->num_philosophers);
	if (!table->forks || !table->philosophers)
	{
		printf("Erreur d'allocation de mémoire.\n");
		if (table->forks)
			free(table->forks);
		if (table->philosophers)
			free(table->philosophers);
		return (1);
	}
	pthread_mutex_init(&table->print_lock, NULL);
	i = 0;
	while (i < table->num_philosophers)
	{
		pthread_mutex_init(&table->forks[i].mutex, NULL);
		table->forks[i].in_use = 0;
		table->philosophers[i].id = i;
		table->philosophers[i].times_eaten = 0;
		table->philosophers[i].last_meal = current_time();
		table->philosophers[i].table = table;
		i++;
	}
	return (0);
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
