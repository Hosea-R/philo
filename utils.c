#include "philo.h"

static int	ft_strcmp(const char *s1, char *s2)
{
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	check_death(t_table *table)
{
	int	i;

	while (!table->stop)
	{
		i = 0;
		while (i < table->num_philosophers)
		{
			if (current_time()
				- table->philosophers[i].last_meal >= table->time_to_die)
			{
				print_action(table, i, "died");
				table->stop = 1;
				break ;
			}
			i++;
		}
		usleep(1000);
	}
}

void	print_action(t_table *table, int philosopher_id, const char *action)
{
	const char	*color;

	pthread_mutex_lock(&table->print_lock);
	if (!table->stop)
	{
		if (ft_strcmp(action, "has taken a fork") == 0)
			color = "\033[1;33m";
		else if (ft_strcmp(action, "is eating") == 0)
			color = "\033[1;32m";
		else if (ft_strcmp(action, "is sleeping") == 0)
			color = "\033[1;34m";
		else if (ft_strcmp(action, "is thinking") == 0)
			color = "\033[1;36m";
		else if (ft_strcmp(action, "died") == 0)
			color = "\033[1;31m";
		else
			color = "\033[0m";
		printf("%s%ld %d %s\033[0m\n", color, get_timestamp(table),
			philosopher_id + 1, action);
	}
	pthread_mutex_unlock(&table->print_lock);
}
