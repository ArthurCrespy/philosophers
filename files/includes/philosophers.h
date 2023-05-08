/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrespy <acrespy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:01:41 by acrespy           #+#    #+#             */
/*   Updated: 2023/04/14 17:51:06 by acrespy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

struct	s_data;
typedef struct timeval	t_time;

typedef struct s_philo
{
	int				id;
	int				id_left;
	int				eat_nb;
	long long		eat_last;
	struct s_data	*data;
	pthread_t		thread;
	pthread_mutex_t	fork;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	data_access;
}					t_philo;

typedef struct s_data
{
	int				philo_nb;
	int				philo_alive;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long long		time_start;
	int				eat_nb;
	t_philo			*philo;
	pthread_t		philo_checker;
	pthread_mutex_t	data_access;
}		t_data;

/* ---------- ARGS --------- */
int			args_check(int argc, char **argv);

/* ---------- INIT --------- */
int			data_init(t_data **data);

/* ---------- DATA --------- */
int			data_parse(t_data **data, int argc, char **argv);
int			data_destroy(t_data **data);

/* ---------- PHILO --------- */
void		*philo_checker(void *arg);
void		*philosopher(void *arg);

/* ---------- TIME --------- */
long long	ft_timestamp(void);
void		ft_wait_start(t_data *data);
void		ft_smart_sleep(t_data *data, long long time);

/* ---------- UTILS --------- */
void		ft_set_dead(t_data *data, int id);
int			ft_check_alive(t_data *data);
void		ft_print_status(t_data *data, int id, char *status);
int			ft_atoi(const char *str);

#endif
