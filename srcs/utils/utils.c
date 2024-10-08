/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:43:19 by mrazanad          #+#    #+#             */
/*   Updated: 2024/10/08 12:43:20 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philosophers.h"

int	string_to_int(const char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 7 && str[i] <= 13)))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + str[i] - '0';
		i++;
	}
	return (result * sign);
}

void	display_status(t_config *config, t_person *person, int state)
{
	pthread_mutex_lock(&config->config_mutex);
	if (state == -1)
		printf("\033[1;32m%ld %d has taken a fork\033[0m\n", current_time()
			- config->start_time, person->id);
	else if (state == 1)
		printf("\033[1;34m%ld %d is thinking\033[0m\n", current_time()
			- config->start_time, person->id);
	else if (state == 2)
		printf("\033[1;33m%ld %d is eating\033[0m\n", current_time()
			- config->start_time, person->id);
	else if (state == 3)
		printf("\033[1;35m%ld %d is sleeping\033[0m\n", current_time()
			- config->start_time, person->id);
	pthread_mutex_unlock(&config->config_mutex);
}

int	validate_input(int argc, char *argv[])
{
	int	i;

	if (argc < 5 || argc > 6)
		return (0);
	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-')
			return (0);
		if (!string_to_int(argv[i]))
			return (0);
		i++;
	}
	return (1);
}
