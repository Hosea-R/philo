/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:26:03 by mrazanad          #+#    #+#             */
/*   Updated: 2024/09/09 13:33:55 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;
	int		i;

	if (argc < 5 || argc > 6)
	{
		printf("%s Invalid number of arguments\n", argv[0]);
		return (1);
	}
	if (init_data(&table, argc, argv) != 0)
		return (1);
	table.start_time = current_time();
	i = 0;
	while (i < table.num_philosophers)
	{
		pthread_create(&table.philosophers[i].thread, NULL, philosopher_life,
			&table.philosophers[i]);
		i++;
	}
	check_death(&table);
	i = 0;
	while (i < table.num_philosophers)
	{
		pthread_join(table.philosophers[i].thread, NULL);
		i++;
	}
	destroy_data(&table);
	return (0);
}
