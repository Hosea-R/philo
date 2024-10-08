/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:43:21 by mrazanad          #+#    #+#             */
/*   Updated: 2024/10/08 12:43:22 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	*philosopher_routine(void *param)
{
	t_args		*args;
	t_person	*person;
	t_config	*config;
	int			has_priority;

	args = (t_args *)param;
	config = args->config;
	person = args->person;
	has_priority = 0;
	while (check_no_dead(config))
	{
		verify_death(config, person);
		has_priority = check_priority(config, person);
		if (has_priority && check_no_dead(config))
		{
			perform_eating(config, person);
			perform_sleeping(config, person);
		}
		if (person->current_state == -1 && check_no_dead(config))
			perform_thinking(config, person);
		delay(0);
	}
	return (args);
}

int	main(int argc, char *argv[])
{
	t_config	config;

	if ((argc == 5 || argc == 6) && validate_input(argc, argv))
	{
		if (argc == 6 && !string_to_int(argv[5]))
			return (0);
		initialize_config(&config, argc, argv);
		start_simulation(&config);
		update_priority_order(&config);
		report_dead_philosopher(&config);
		cleanup_config(&config);
	}
	else
		printf("Invalid input\n");
	return (0);
}
