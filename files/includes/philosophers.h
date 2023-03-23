/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:01:41 by acrespy           #+#    #+#             */
/*   Updated: 2023/03/16 13:01:41 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
#include <sys/time.h>

typedef struct timeval t_time;

typedef struct s_philo
{
	int				id;
	int				nb_eat;
	int				last_eat;
	pthread_t		thread;
	pthread_mutex_t fork;
	struct s_philo	*next;
}				t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	int 			all_alive;
	t_time			time;
	t_time			time_start;
	t_time 			time_stop;
	t_philo			*philo;
}				t_data;

/* ---------- ARGS --------- */
int	args_check(int argc, char **argv);

/* --------- CREATE -------- */
void create_table(t_data **data);

/* ---------- DATA --------- */
int	data_parse(t_data *data, int argc, char **argv);

/* ---------- PHILO --------- */
void	*philosopher(void *arg);

/* ---------- UTILS --------- */
void go_to_philo(t_data **data, int id);
void	free_table(t_data *data);
void	print_table(t_data *data);
int		ft_timecode(t_data *data);

#endif