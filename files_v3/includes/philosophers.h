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
# include <sys/time.h>

typedef struct timeval t_time;

typedef struct s_data
{
	int				id_tmp;
	int				philo_nb;
	int				philo_alive;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_nb;
	int			    *philo_eat_nb;
	pthread_t		*philo_thread;
	pthread_mutex_t *fork;
}               t_data;

/* ---------- ARGS --------- */
int	args_check(int argc, char **argv);


/* ---------- INIT --------- */

/* ---------- DATA --------- */
int data_parse(t_data **data, int argc, char **argv);
int	data_init(t_data **data);

/* ---------- PHILO --------- */

/* ---------- UTILS --------- */
int	ft_atoi(const char *str);

#endif