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

typedef struct s_philo
{
	int				id;
	//pthread_mutex_t fork_mutex;
	int				fork_avail;
	int			    eat_last;
	int				eat_count;
	pthread_t		thread;
	//struct s_data	*data;
	struct s_philo	*next;
}				t_philo;

typedef struct s_data
{
	int             id_tmp;
	int				nb_eat;
	int				nb_philo;
	int 			all_alive;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	t_time			time;
	t_time			time_start;
	t_time 			time_stop;
	t_philo			*philo;
	pthread_mutex_t data_access;
}				t_data;

/* ---------- ARGS --------- */
int		args_check(int argc, char **argv);

/* --------- CREATE -------- */
void	create_table(t_data **data);

/* ---------- DATA --------- */
int		data_parse(t_data *data, int argc, char **argv);

/* ---------- PHILO --------- */
int		philo_is_dead(t_data *data, int id);
void	philo_eat(t_data *data, int id);
void	philo_sleep(t_data *data, int id);
void	philo_think(t_data *data, int id, int ttt);
void	*philosopher(void *arg);

/* ---------- UTILS --------- */
void	table_free(t_data *data);
void	table_print(t_data *data);
void	ft_goto_philo(t_data **data, int id);
int		ft_timecode(t_data *data);
void	ft_wait(t_data *data, int id, int time);
#endif
