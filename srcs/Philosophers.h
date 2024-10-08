/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:43:28 by mrazanad          #+#    #+#             */
/*   Updated: 2024/10/08 12:43:28 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_config	t_config;
typedef struct s_person	t_person;

typedef struct s_args
{
	t_config			*config;
	t_person			*person;
}						t_args;

typedef struct s_config
{
	int					num_philosophers;
	t_person			**people;
	int					death_time;
	
	int					eat_duration;
	int					sleep_duration;
	int					eat_count;
	int					finished_count;
	int					no_dead_philos;
	int					dead_philosopher;
	int					*priority_order;
	size_t				start_time;
	pthread_mutex_t		config_mutex;
}						t_config;

/*
** state
** -1: none
** 0: dead
** 1: thinking
** 2: eating
** 3: sleeping
*/
typedef struct s_person
{
	pthread_t			thread_id;
	int					id;
	int					current_state;
	int					meal_count;
	size_t				last_meal_time;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		person_mutex;
}						t_person;

void					initialize_config(t_config *config, int argc, char *argv[]);
void					cleanup_config(t_config *config);

void					*philosopher_routine(void *arg);
t_person				*create_person(int id);
void					initialize_people(t_config *config);
void					start_simulation(t_config *config);

void					setup_priority(t_config *config);
void					calculate_priority(t_config *config);
int						check_priority(t_config *config, t_person *person);
void					update_priority_order(t_config *config);

size_t					current_time(void);
void					delay(int ms);

void					perform_eating(t_config *config, t_person *person);
void					perform_sleeping(t_config *config, t_person *person);
void					perform_thinking(t_config *config, t_person *person);

int						check_no_dead(t_config *config);
void					verify_death(t_config *config, t_person *person);
void					report_dead_philosopher(t_config *config);

int						string_to_int(const char *str);
void					display_status(t_config *config, t_person *person, int state);
int						validate_input(int argc, char *argv[]);

#endif
